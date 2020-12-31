#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day1/floors.h"


int main(void){
  char* path = "src/day1/instructions.txt";
  char* input = getFileContent(path);

  printf("%d\n", getFloor(input, FALSE));
  printf("%d\n", getFloor(input, TRUE));

  return 0;
}


int getFloor(char* instructions, int onlyGetBasement){
  int floor = 0;
  for (int i = 0; i< strlen(instructions); i++){
    if (instructions[i] == '('){
      floor++;
    } else if (instructions[i] == ')'){
        floor--;
    }
    if (onlyGetBasement && floor == -1){
      return i+1;
    }
  }
  return floor;
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
