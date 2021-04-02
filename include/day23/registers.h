#ifndef REGISTERS_H
#define REGISTERS_H


char*** createInstructions(char* input, int* size);
void doInstructions(char*** instructions, int size, int* a, int* b);


#endif