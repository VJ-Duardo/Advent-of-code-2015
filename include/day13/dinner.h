#ifndef DINNER_H
#define DINNER_H


int** createDistanceMatrix(char** lines, int size, int* memSize);
void getBiggestHappinessChange(int** matrix, int* circle, int members, int* biggest, int curr);


#endif