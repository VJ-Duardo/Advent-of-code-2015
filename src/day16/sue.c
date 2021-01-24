#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "day16/sue.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day16/aunts.txt");
  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);

  char* theAunt[] = {"children", "3", "cats", "7", "samoyeds", "2", "pomeranians", "3", "akitas", "0",
                    "vizslas",  "0", "goldfish", "5", "trees", "3", "cars", "2", "perfumes", "1"};
  char*** aunts = getAunts(linesArray, lines);
  
  printf("%d\n", getRightAunt(aunts, theAunt, lines));

  return 0;
}


char*** getAunts(char** lines, int size){
  char*** aunts = (char***) malloc(size*sizeof(char**));
  for (int i = 0; i < size; i++){
    int partsSize = 0;
    char** parts = getSplitArray(lines[i], ": ,", &partsSize);

    aunts[i] = (char**) malloc(AUNT_ELEMS*sizeof(char*));
    for (int j=2, k=0; k<AUNT_ELEMS; j++, k++){
      aunts[i][k] = (char*) malloc(sizeof(parts[j]+1));
      strcpy(aunts[i][k], parts[j]);
    }

    for (int l = 0; l < partsSize; l++){
      free(parts[l]);
    }
    free(parts);
    free(lines[i]);
  }
  free(lines);
  return aunts;
}


int getRightAunt(char*** aunts, char** theAunt, int size){
  for (int i =0; i < size; i++){
    int invalid = false;
    for (int j =0; j < AUNT_ELEMS; j+=2){
      for (int k=0; k < THE_AUNT_ELEMS; k+=2){
        if (!strcmp(aunts[i][j], theAunt[k])){
          if (!strcmp(theAunt[k], "cats") || !strcmp(theAunt[k], "trees")){
            if (atoi(aunts[i][j+1]) <= atoi(theAunt[k+1]))
              invalid = true;
          }else if (!strcmp(theAunt[k], "pomeranians") || !strcmp(theAunt[k], "goldfish")){
            if (atoi(aunts[i][j+1]) >= atoi(theAunt[k+1]))
              invalid = true;
          }else if (strcmp(aunts[i][j+1], theAunt[k+1])){
            invalid = true;
          }
          break;
        }
      }
      if (invalid){
        break;
      }
    }
    if (!invalid){
      return i+1;
    }
  }
  return 0;
}