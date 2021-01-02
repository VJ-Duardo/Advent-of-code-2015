#ifndef DELIVERY_H
#define DELIVERY_H


#define TRUE 1
#define FALSE 0

typedef struct house {
  int x, y, presents;
} House;

House* doRoute(char* input, int* size, int* starts, int interval);


#endif
