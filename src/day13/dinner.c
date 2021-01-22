#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day13/dinner.h"
#include "utils/utils.h"


int main(void){
  //awful code in this one
  char* input = getFileContent((char*)"src/day13/family.txt");
  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);

  int members = 0;
  int** distanceMatrix = createDistanceMatrix(linesArray, lines, &members);

  int circle[members];
  int result = 0;
  getBiggestHappinessChange(distanceMatrix, circle, members, &result, members);
  printf("%d\n", result);

  
  members++;
  int** matrixPlusMe = (int**) malloc(members*sizeof(int*));
  for (int i = 0; i < members; i++){
    matrixPlusMe[i] = (int*) malloc(members*sizeof(int));
    for (int j = 0; j < members; j++){
      matrixPlusMe[i][j] = 0;
    }
  }
  for (int i = 0; i < members-1; i++){
    for (int j = 0; j < members-1; j++){
      matrixPlusMe[i][j] = distanceMatrix[i][j];
    }
  }
  free(distanceMatrix);

  int newCircle[members];
  result = 0;
  getBiggestHappinessChange(matrixPlusMe, newCircle, members, &result, members);
  printf("%d\n", result);

  return 0;
}


static int getHappinessChange(int* circle, int** matrix, int members){
  int c = 0;
  for (int i = 0; i < members-1; i++){
    c += matrix[circle[i]][circle[i+1]];
    c += matrix[circle[i+1]][circle[i]];
  }
  c += matrix[circle[members-1]][circle[0]];
  c += matrix[circle[0]][circle[members-1]];
  return c;
}


void getBiggestHappinessChange(int** matrix, int* circle, int members, int* biggest, int curr){
  if (curr == 0){
    int change = getHappinessChange(circle, matrix, members);
    *biggest = (change > *biggest) ? change : *biggest;
    return;
  }
  for (int i= 0; i < members; i++){
    int next = 0;
    for (int j=0; j < members; j++){
      if (circle[j] == i){
        next = 1;
        break;
      }
    }
    if (next){
      continue;
    } else {
      circle[members-curr] = i;
      getBiggestHappinessChange(matrix, circle, members, biggest, curr-1);
    }
  }
  circle[members-curr] = -1;
}


static int getIndex(char** array, char* elem, int size){
  for (int i = 0; i < size; i++){
    if (!strcmp(array[i], elem)){
      return i;
    }
  }
  return -1;
}

int** createDistanceMatrix(char** lines, int size, int* memSize){
  int membersSize = 0;
  char** members = (char**) NULL;
  int** matrix = (int**) malloc(sizeof(int*));
  for (int i = 0; i < size; i++){
    int _;
    char** parts = getSplitArray(lines[i], " .", &_);
    int fromToIndex[2];
    for (int j = 0; j <=10; j+=10){
      int index = getIndex(members, parts[j], membersSize);
      if (index == -1){
        index = membersSize++;
        members = realloc(members, membersSize*sizeof(char*));
        members[index] = parts[j];
        matrix = realloc(matrix, membersSize*sizeof(int*));
        matrix[index] = (int*)malloc(membersSize*sizeof(int));
        matrix[index][index] = 0;
      }
      fromToIndex[(j==10) ? 1 : j] = index;
    }
    matrix[fromToIndex[0]][fromToIndex[1]] = (!strcmp(parts[2], "lose")) ? atoi(parts[3]) * -1 : atoi(parts[3]);

    free(parts);
  }
  free(members);
  *memSize = membersSize;
  return matrix;
}