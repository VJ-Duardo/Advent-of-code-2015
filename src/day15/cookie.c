#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day15/cookie.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day15/ingredients.txt");
  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);

  int** ingredients = getIngredients(linesArray, lines);

  int result = 0;
  int fractions[lines];
  for (int i=0; i < lines; fractions[i++]=0);
  getTotalHighestCookie(ingredients, lines, lines, fractions, &result);

  printf("%d\n", result);

  return 0;
}


static int getTotal(int** ingredients, int size, int* fractions){
  int totals[size];
  for (int i =0; i < PROPERTIES; i++){
    int total = 0;
    for (int j =0; j < size; j++){
      total += fractions[j]*ingredients[j][i];
    }
    if (total <= 0){
      return 0;
    } else {
      totals[i] = total;
    }
  }
  if (totals[PROPERTIES-1] != 500){
    return 0;
  }
  int prod = 1;
  for (int i = 0; i < PROPERTIES-1; i++){
    prod*= totals[i];
  }
  return prod;
}


void getTotalHighestCookie(int** ingredients, int size, int curr, int* fractions, int* biggest){
  if (curr == 0){
    int total = getTotal(ingredients, size, fractions);
    *biggest = (total > *biggest) ? total : *biggest;
    return;
  }
  int sum = 0;
  for (int k=0; k < size; k++){
    sum += fractions[k];
  }
  if (curr > 1){
    for (int i=0; i < 101-sum; i++){
      fractions[size-curr] = i;
      getTotalHighestCookie(ingredients, size, curr-1, fractions, biggest);
    }
  } else {
    fractions[size-curr] = 100-sum;
    getTotalHighestCookie(ingredients, size, curr-1, fractions, biggest);
  }
  fractions[size-curr] = 0;
}


int** getIngredients(char** lines, int size){
  int** ingredients = (int**) malloc(size*sizeof(int*));
  for (int i = 0; i < size; i++){
    int partsSize = 0;
    char** parts = getSplitArray(lines[i], " ,", &partsSize);

    ingredients[i] = (int*) malloc(PROPERTIES*sizeof(int));
    for (int j=2, k=0; k < PROPERTIES; j+= 2, k++){
      ingredients[i][k] = atoi(parts[j]);
    }

    for (int k=0; k<partsSize; k++){
      free(parts[k]);
    }
    free(parts);
    free(lines[i]);
  }
  free(lines);
  return ingredients;
}