#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day8/characters.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day8/strings.txt");

  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);

  printf("%d\n", getResult(linesArray, lines, 1));
  printf("%d\n", getResult(linesArray, lines, 2));

  return 0;
}

static int getRealLen(char* line){
  int c = 2;
  for (int i = 1; i < strlen(line)-1; i++){
    if (line[i] == '\\'){
      c++;
      i++;
      if (line[i] == 'x'){
        c+= 2;
        i+= 2;
      }
    }
  }
  return c;
}

static int getNewLen(char* line){
  int c = strlen(line)+4;
  for (int i = 1; i < strlen(line)-1; i++){
    if (line[i] == '\\'){
      if (line[i+1] == 'x'){
        c++;
        i+= 3;
      } else {
        c+= 2;
        i++;
      }
    }
  }
  return c;
}

int getResult(char** strings, int size, int part){
  int all = 0;
  int new = 0;
  for (int i = 0; i<size; i++){
    all += strlen(strings[i]);
    new += (part==1) ? (strlen(strings[i])-getRealLen(strings[i])) : getNewLen(strings[i]);
  }
  return abs(all-new);
}