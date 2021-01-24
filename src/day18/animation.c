#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day18/animation.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day18/grid.txt");
  int lines = 0;
  char** grid = getSplitArray(input, "\n", &lines);
  grid[0][0] = ON;
  grid[0][GRID_WIDTH-1] = ON;
  grid[GRID_HEIGHT-1][0] = ON;
  grid[GRID_HEIGHT-1][GRID_WIDTH-1] = ON;

  printf("%d\n", getLightsAfterSteps(grid, 100));
  

  return 0;
}



int getLightsAfterSteps(char** initGrid, int steps){
  char** grid = createNewGrid(initGrid);
  for (int i = 0; i < steps-1; i++){
    grid = createNewGrid(grid);
  }

  int c = 0;
  for (int y =0; y < GRID_HEIGHT; y++){
    for (int x=0; x < GRID_WIDTH; x++){
      if (grid[y][x] == ON){
        c++;
      }
    }
  }
  return c;
}



static int countNeighbours(char** grid, int y, int x){
  int c = 0;
  for (int i=-1; i <= 1; i++){
    for (int j=-1; j <= 1; j++){
      if ((x+j >= 0 && x+j < GRID_WIDTH) && (y+i >= 0 && y+i < GRID_HEIGHT)){
        c = (grid[y+i][x+j] == ON) ? c+1 : c;
      }
    }
  }
  return (grid[y][x] == ON) ? c-1 : c;
}


char** createNewGrid(char** grid){
  char** newGrid = (char**) malloc(GRID_HEIGHT*sizeof(char*));
  for (int y =0; y < GRID_HEIGHT; y++){
    newGrid[y] = (char*) malloc(GRID_WIDTH);
    for (int x=0; x < GRID_WIDTH; x++){
      int neighbours = countNeighbours(grid, y, x);
      if (grid[y][x] == ON && neighbours != 2 && neighbours != 3){
        newGrid[y][x] = OFF;
      }else if(grid[y][x] == OFF && neighbours == 3){
        newGrid[y][x] = ON;
      } else {
        newGrid[y][x] = grid[y][x];
      }
    }
  }
  newGrid[0][0] = ON;
  newGrid[0][GRID_WIDTH-1] = ON;
  newGrid[GRID_HEIGHT-1][0] = ON;
  newGrid[GRID_HEIGHT-1][GRID_WIDTH-1] = ON;

  for (int i =0; i < GRID_HEIGHT; i++){
    free(grid[i]);
  }
  free(grid);
  return newGrid;
}