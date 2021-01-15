#ifndef GA_H
#define GA_H

#define POP_SIZE 100
#define TOURNAMENT_SIZE 50
#define ELITE_SIZE 10
#define PCROSS 60
#define PMUT 1

int getFitness(int* individual, int size, int** distanceMatrix);
int** getPopulation(int generations, int** distanceMatrix, int individSize);
int** doTournamentSelection(int** population, int** distanceMatrix, int individSize, int** elite);
int** doRecombination(int** population, int individSize);
void doMutation(int** population, int individSize);
int** doGeneration(int** population, int** distanceMatrix, int individSize);
int getBestRoute(int** population, int size, int** distanceMatrix);


#endif