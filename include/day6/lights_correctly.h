#ifndef LIGHTS_CORRECTLY_H
#define LIGHTS_CORRECTLY_H

#include <stdbool.h>
#include "day6/lights.h"


int** makeGridCorrectly(int height, int width);
void doAllInstructionsCorrectly(Instruction* instructions, int** grid, int size);
int countTotalBrightness(int** grid);


#endif
