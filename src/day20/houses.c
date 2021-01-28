#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "day20/houses.h"


int main(void){
  int input = 33100000;
  printf("%d\n", getLowestHouseNum(input, 10, 1));
  printf("%d\n", getLowestHouseNum(input, 11, 2));

  return 0;
}


int getLowestHouseNum(int input, int ppH, int part){
  input = ceil(input/ppH);
  int* houses = (int*) malloc(input*sizeof(int));
  for (int i=1; i<= input; i++){
    for (int j=i; j<= ((part==1)?input:i+50*i); j+=i){
      if (j <= input+1){
        houses[j-1] += i;
      } else {
        break;
      }
    }
  }
  for (int i=0; i < input; i++){
    if (houses[i] >= input){
      free(houses);
      return i+1;
    }
  }
  
  free(houses);
  return -1;
}