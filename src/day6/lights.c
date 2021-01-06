#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

#include "day6/lights.h"
#include "day6/lights_correctly.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day6/instructions.txt");
  bool** grid = makeGrid(GRID_HEIGHT, GRID_WIDTH);
  int** correctGrid = makeGridCorrectly(GRID_HEIGHT, GRID_WIDTH);

  int instructs = 0;
  char** linesArray = getSplitArray(input, "\n", &instructs);
  Instruction* instructsArray = makeInstructsArray(linesArray, instructs);

  doAllInstructions(instructsArray, grid, instructs);
  printf("%d\n", countLitLights(grid));

  doAllInstructionsCorrectly(instructsArray, correctGrid, instructs);
  printf("%d\n", countTotalBrightness(correctGrid));

  return 0;
}


static void updateGrid(Instruction instr, bool** grid){
  for (int i = instr.y1; i <= instr.y2; i++){
    for (int j = instr.x1; j <= instr.x2; j++){
      if (!strcmp(instr.task, "toggle")){
        grid[i][j] = !grid[i][j];
      } else {
        grid[i][j] = (!strcmp(instr.task, "on")) ? true : false;
      }
    }
  }
}


void doAllInstructions(Instruction* instructions, bool** grid, int size){
  for (int i = 0; i < size; i++){
    updateGrid(instructions[i], grid);
  }
}


int countLitLights(bool** grid){
  int c = 0;
  for (int i = 0; i < GRID_HEIGHT; i++){
    for (int j = 0; j < GRID_WIDTH; j++){
      if (grid[i][j]){
        c++;
      }
    }
  }
  return c;
}



bool** makeGrid(int height, int width){
  bool** grid = (bool**) malloc(height*sizeof(bool*));
  for (int i = 0; i < height; i++){
    grid[i] = (bool*) malloc(width*sizeof(bool));
    for(int j = 0; j < width ; grid[i][j++] = false);
  }
  return grid;
}



static char** getMatches(char* line){
  regex_t regex;
  size_t maxMatches = 5;
  size_t subMatches = 1;
  regmatch_t matchArray[subMatches];

  regcomp(&regex, "off|on|toggle|[0-9]+", REG_EXTENDED);

  char** matches = (char**) malloc(maxMatches*sizeof(char*));

  for (int i = 0; i < maxMatches; i++) {
    if (regexec(&regex, line, subMatches, matchArray, 0)){
      break;
    }

    unsigned int offset = matchArray[0].rm_eo;

    char* tempCursor = (char*)malloc(strlen(line)+1);
    strcpy(tempCursor, line);
    tempCursor[matchArray[0].rm_eo] = 0;
    matches[i] = tempCursor + matchArray[0].rm_so;
    line += offset;
  }

  regfree(&regex);

  return matches;
}


Instruction* makeInstructsArray(char** lines, int size){
  Instruction* instrs = (Instruction*)malloc(size*sizeof(Instruction));
  for (int i = 0; i < size; i++){
    char** params = getMatches(lines[i]);
    Instruction instr = {.task=params[0],
      .x1=atoi(params[1]), .y1=atoi(params[2]),
      .x2=atoi(params[3]), .y2=atoi(params[4])};
    instrs[i] = instr;
  }
  return instrs;
}
