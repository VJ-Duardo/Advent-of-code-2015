#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "day9/tsp.h"
#include "day9/ga.h"
#include "utils/utils.h"


int part = 1;


int main(void){
  srand(time(NULL));
  char* input = getFileContent((char*)"src/day9/locations.txt");

  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);
  int locations = 0;
  int** distanceMatrix = createDistanceMatrix(linesArray, lines, &locations);
  
  int** population = getPopulation(2000, distanceMatrix, locations);
  printf("%d\n", getBestRoute(population, locations, distanceMatrix));
  
  part = 2;
  population = getPopulation(2000, distanceMatrix, locations);
  printf("%d\n", abs(getBestRoute(population, locations, distanceMatrix)));

  return 0;
}


static int getIndex(char** array, char* elem, int size){
  for (int i = 0; i < size; i++){
    if (!strcmp(array[i], elem)){
      return i;
    }
  }
  return -1;
}

int** createDistanceMatrix(char** lines, int size, int* locationSize){
  int locs = 0;
  char** locations = (char**) NULL;
  int** matrix = (int**) malloc(sizeof(int*));
  for (int i = 0; i < size; i++){
    int _;
    char** parts = getSplitArray(lines[i], " ", &_);
    int fromToIndex[2];
    for (int j = 0; j <=2; j+=2){
      int index = getIndex(locations, parts[j], locs);
      if (index == -1){
        index = locs++;
        locations = realloc(locations, locs*sizeof(char*));
        locations[index] = parts[j];
        (*locationSize)++;
        matrix = realloc(matrix, locs*sizeof(int*));
        matrix[index] = (int*)malloc(locs*sizeof(int));
        matrix[index][index] = 0;
      }
      fromToIndex[(j==2) ? 1 : j] = index;
    }
    matrix[fromToIndex[1]][fromToIndex[0]] = atoi(parts[4]);
    matrix[fromToIndex[0]][fromToIndex[1]] = atoi(parts[4]);
    
    free(parts);
  }
  free(locations);
  return matrix;
}