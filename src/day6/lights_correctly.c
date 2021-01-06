#include <stdlib.h>
#include <string.h>

#include "day6/lights_correctly.h"



int** makeGridCorrectly(int height, int width){
  int** grid = (int**) malloc(height*sizeof(int*));
  for (int i = 0; i < height; i++){
    grid[i] = (int*) malloc(width*sizeof(int));
    for(int j = 0; j < width ; grid[i][j++] = 0);
  }
  return grid;
}

static void updateGridCorrectly(Instruction instr, int** grid){
  for (int i = instr.y1; i <= instr.y2; i++){
    for (int j = instr.x1; j <= instr.x2; j++){
      if (!strcmp(instr.task, "toggle")){
        grid[i][j] += 2;
      } else if ((!strcmp(instr.task, "on"))){
        grid[i][j]++;
      } else {
        if (grid[i][j] > 0){
          grid[i][j]--;
        }
      }
    }
  }
}

void doAllInstructionsCorrectly(Instruction* instructions, int** grid, int size){
  for (int i = 0; i < size; i++){
    updateGridCorrectly(instructions[i], grid);
  }
}

int countTotalBrightness(int** grid){
  int c = 0;
  for (int i = 0; i < GRID_HEIGHT; i++){
    for (int j = 0; j < GRID_WIDTH; j++){
      c += grid[i][j];
    }
  }
  return c;
}
