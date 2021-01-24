#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "day17/eggnog.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day17/containers.txt");
  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);

  int* containers = createContainerArray(linesArray, lines);

  int result = 0;
  int min = lines;
  int minCount = 0;
  countContainers(containers, lines, 150, 0, 0, &result, 0, &min, &minCount);
  printf("%d\n", result);
  printf("%d\n", minCount);

  return 0;
}



void countContainers(int* containers, int size, int liters, int curr, int sum, int* r, int c, int* min, int* mins){
  if (sum >= liters){
    if (sum == liters){
      if (c < *min){
        *mins = 1;
        *min = c;
      } else if (c == *min){
        (*mins)++;
      }
      (*r)++;
    }
    return;
  }
  for (int i=curr; i < size; i++){
    countContainers(containers, size, liters, i+1, sum+containers[i], r, c+1, min, mins);
  }
}


static int cmpfunc (const void* a, const void* b) {
   return ( *(int*)b - *(int*)a );
}

int* createContainerArray(char** lines, int size){
  int* containers = (int*) malloc(size*sizeof(int));
  for (int i = 0; i < size; i++){
    containers[i] = atoi(lines[i]);
    free(lines[i]);
  }
  free(lines);
  qsort(containers, size, sizeof(int), cmpfunc);
  return containers;
}