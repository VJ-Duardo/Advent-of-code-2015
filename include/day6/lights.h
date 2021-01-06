#ifndef LIGHTS_H
#define LIGHTS_H


#define GRID_HEIGHT 1000
#define GRID_WIDTH 1000

typedef struct instr {
  int x1, y1, x2, y2;
  char* task;
} Instruction;

bool** makeGrid(int height, int width);
Instruction* makeInstructsArray(char** lines, int size);
void doAllInstructions(Instruction* instructions, bool** grid, int size);
int countLitLights(bool** grid);


#endif
