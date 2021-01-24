#ifndef ANIMATION_H
#define ANIMATION_H


#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define ON '#'
#define OFF '.'

int getLightsAfterSteps(char** initGrid, int steps);
char** createNewGrid(char** grid);


#endif