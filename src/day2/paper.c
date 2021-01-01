#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day2/paper.h"


int main(void){
  char* path = "src/day2/presents.txt";
  char* input = getFileContent(path);

  int elemSize = 0;
  char** splitArray = getSplitArray(input, "\n", &elemSize);
  int** presentArray = getPresentsArray(splitArray, elemSize);

  int paper = 0;
  int ribbon = 0;
  getNeededUtils(presentArray, elemSize, &paper, &ribbon);
  printf("%d\n", paper);
  printf("%d\n", ribbon);

  return 0;
}


static int cmpfunc (const void* a, const void* b) {
   return ( *(int*)a - *(int*)b );
}

void getNeededUtils(int** presents, int size, int* area, int* ribbon){
  for (int i = 0; i < size; i++){
    qsort(presents[i], DIMENSIONS, sizeof(int), cmpfunc);
    int x = presents[i][0], y = presents[i][1], z = presents[i][2];
    *area += 2*x*y + 2*x*z + 2*y*z + x*y;
    *ribbon += 2*x + 2*y + x*y*z;
  }
}


int** getPresentsArray(char** input, int size){
  int **presents = (int**) malloc(size*sizeof(int*));
  for (int i=0; i < size; i++){
    presents[i] = (int*)malloc(DIMENSIONS*sizeof(int));
    char *dim = strtok(input[i], "x");
    for (int j=0; j<DIMENSIONS; j++){
      presents[i][j] = atoi(dim);
      dim = strtok(NULL, "x");
    }
  }
  return presents;
}


char** getSplitArray(char* input, const char* del, int* size){
  char *s = strtok(input, del);
  char **result = (char**) malloc(sizeof(char*));
  int c = 0;
  while (s != NULL){
    (*size)++;
    result = realloc(result, *size*sizeof(char*));
    result[c] = (char*)malloc(strlen(s)*sizeof(char));
    result[c] = s;
    c++;
    s = strtok(NULL, del);
  }
  return result;
}

char* getFileContent(char* path){
  FILE *file;
  int c, size = 1, i = 0;
  char* content = malloc(1);
  file = fopen(path, "r");
  if (file){
    while ((c = getc(file)) != EOF){
      size++;
      content = realloc(content, size * sizeof(char));
      content[i++] = c;
    }
    fclose(file);
    return content;
  }
  return (char*)"";
}
