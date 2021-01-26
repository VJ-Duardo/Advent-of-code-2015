#ifndef MEDICINE_H
#define MEDICINE_H

typedef struct rep {
  char* from;
  char* to;
} Rep;
Rep** createReps(char** lines, int size, int* newSize);
int doAllReplacements(Rep** replacements, char* molecule, int size);
int doMoleculeFabrication(Rep** replc, int size, char* molecule, int count);


#endif