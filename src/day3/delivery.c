#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day3/delivery.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day3/directions.txt");

  int houses = 0;
  House* houseArray = doRoute(input, &houses, (int[]){0}, 1);
  printf("%d\n", houses);
  free(houseArray);

  houses = 0;
  houseArray = doRoute(input, &houses, (int[]){0, 1}, 2);
  printf("%d\n", houses);

  return 0;
}


static int checkHouses(House* houses, int size, int x, int y){
  for (int i = 0; i < size; i++){
    if (houses[i].x == x && houses[i].y == y){
      houses[i].presents++;
      return TRUE;
    }
  }
  return FALSE;
}

House* doRoute(char* input, int* size, int* starts, int interval){
  *size = 1;
  House* houses = (House*) malloc(sizeof(House));
  House inital = {.x=0, .y=0, .presents=interval};
  houses[0] = inital;
  for (int j = 0; j < interval; j++){
    int x = 0, y = 0;
    for (int i = starts[j]; i < strlen(input); i+= interval){
      switch(input[i]){
        case '>': x++; break;
        case '<': x--; break;
        case '^': y++; break;
        case 'v': y--; break;
        default: continue;
      }
      if (!checkHouses(houses, *size, x, y)){
        (*size)++;
        houses = (House*)realloc(houses, *size * sizeof(House));
        House newHouse = {.x=x, .y=y, .presents=1};
        houses[(*size)-1] = newHouse;
      }
    }
  }
  return houses;
}
