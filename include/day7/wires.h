#ifndef WIRES_H
#define WIRES_H

#include <stdbool.h>

typedef struct wire {
  char* name;
  int value;
  char** srcs;
  char* op;
  int opVal;
  bool done;
} Wire;

Wire* createWires(char** lines, int size);
int getSignal(Wire* wireArray, char* wire, int wires);


#endif
