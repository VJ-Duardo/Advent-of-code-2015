#ifndef EGGNOG_H
#define EGGNOG_H


int* createContainerArray(char** lines, int size);
void countContainers(int* containers, int size, int liters, int curr, int sum, int* r, int c, int* min, int* mins);
#endif