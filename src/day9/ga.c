#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day9/ga.h"



static void shuffleArray(int* array, int size){
  for (int i= 0; i< size; i++){
    int index = rand() % size;
    int temp = array[index];
    array[index] = array[i];
    array[i] = temp;
  }
}

static int** createInitialPopulation(int popSize, int individSize){
  int** population = (int**) malloc(popSize*sizeof(int*));
  for (int i = 0; i < popSize; i++){
    int* individual = (int*) malloc(individSize*sizeof(int));
    for (int j=0; j<individSize; j++){
      individual[j] = j;
    }
    shuffleArray(individual, individSize);
    population[i] = individual;
  }
  return population;
}

static void sortPopulation(int** population, int* fitnessScores) {
  int i, j, *tmp;
  for (i = 1; i < POP_SIZE; i++){
    for (j = 0; j < POP_SIZE - 1 ; j++) {
      if (fitnessScores[j] > fitnessScores[j+1]) {
        tmp = population[j];
        population[j] = population[j+1];
        population[j+1] = tmp;
      }
    }
  }
}



int getFitness(int* individual, int size, int** distanceMatrix){
  extern int part;
  int f = 0;
  for (int i = 0; i < size-1; i++){
    if (part == 1){
      f += distanceMatrix[individual[i]][individual[i+1]];
    } else {
      f -= distanceMatrix[individual[i]][individual[i+1]];
    }
  }
  return f;
}


int getBestRoute(int** population, int size, int** distanceMatrix){
  int best = getFitness(population[0], size, distanceMatrix);
  for (int i= 0; i < POP_SIZE; i++){
    int fitness = getFitness(population[i], size, distanceMatrix);
    free(population[i]);
    if (fitness < best){
      best = fitness;
    }
  }
  free(population);
  return best;
}



int** getPopulation(int generations, int** distanceMatrix, int individSize){
  int** population = createInitialPopulation(POP_SIZE, individSize);
  for (int i=0; i<generations-1; i++){
    population = doGeneration(population, distanceMatrix, individSize);
  }
  return population;
}


int** doTournamentSelection(int** population, int** distanceMatrix, int individSize, int** elite){
  int fitnessScores[POP_SIZE];
  for (int i= 0; i < POP_SIZE; i++){
    fitnessScores[i] = getFitness(population[i], individSize, distanceMatrix);
  }
  
  sortPopulation(population, fitnessScores);
  for (int i=0; i < ELITE_SIZE; i++){
    elite[i] = population[i];
  }
  
  int** matingPool = (int**) malloc(POP_SIZE*sizeof(int*));
  for (int i= 0; i < POP_SIZE; i++){
    int tournament[TOURNAMENT_SIZE];
    for (int j =0; j < TOURNAMENT_SIZE; j++){
      tournament[j] = rand() % POP_SIZE;
    }
    int best = tournament[0];
    for (int k=1; k<TOURNAMENT_SIZE; k++){
      best = (fitnessScores[tournament[k]] < fitnessScores[best]) ? tournament[k] : best;
    }
    matingPool[i] = population[best];
  }
  free(population);
  return matingPool;
}


int** doRecombination(int** population, int individSize){
  int** newChildren = (int**) malloc(POP_SIZE*sizeof(int*));
  for (int i= ELITE_SIZE; i < POP_SIZE; i+= 2){
    int* children[2];
    int* parents[2];
    for (int l=0; l<2; l++){
      children[l] = (int*) malloc(individSize*sizeof(int));
      parents[l] = population[rand() % POP_SIZE];
    }
    if ((rand() % 100) > PCROSS){
      for (int m = 0; m< 2; m++){
        for (int n = 0; n< individSize; n++){
          children[m][n] = parents[m][n];
        }
        newChildren[i+m] = children[m];
      }
      continue;
    }
    for (int k=0; k<2; k++){
      int randomSub = rand() % (individSize-1);
      children[k][0] = parents[k][randomSub];
      children[k][1] = parents[k][randomSub+1];
      int c = 0;
      for (int j=2; j<individSize; j++){
        while ((parents[!k][c] == children[k][0]) || (parents[!k][c] == children[k][1])){
          c++;
        }
        children[k][j] = parents[!k][c];
        c++;
      }
      newChildren[i+k] = children[k];
    }
  }
  free(population);
  return newChildren;
}


void doMutation(int** population, int individSize){
  for (int i = 0; i < POP_SIZE; i++){
    for (int j= 0; j < individSize; j++){
      if ((rand() % 100) < PMUT){
        int index = rand() % individSize;
        int temp = population[i][index];
        population[i][index] = population[i][j];
        population[i][j] = temp;
      }
    }
  }
}


int** doGeneration(int** population, int** distanceMatrix, int individSize){
  int** elite = (int**) malloc(ELITE_SIZE*sizeof(int*));
  population = doTournamentSelection(population, distanceMatrix, individSize, elite);
  population = doRecombination(population, individSize);
  for (int i=0; i < ELITE_SIZE; i++){
    population[i] = elite[i];
  }
  //free(elite);
  doMutation(population, individSize);
  return population;
}

