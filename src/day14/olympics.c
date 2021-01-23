#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "day14/olympics.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day14/reindeers.txt");
  int lines = 0;
  char** linesArray = getSplitArray(input, "\n", &lines);

  Reindeer** reindeers = createReindeers(linesArray, lines);

  printf("%d\n", getBestReindeer(reindeers, lines, 2503));
  printf("%d\n", getMostValue(reindeers, lines, false));

  return 0;
}


Reindeer** createReindeers(char** lines, int size){
  Reindeer** reindeers = (Reindeer**) malloc(size*sizeof(Reindeer*));
  for (int i = 0; i < size; i++){
    int partSize = 0;
    char** parts = getSplitArray(lines[i], " ", &partSize);
    
    Reindeer *newDeer = (Reindeer*)malloc(sizeof(Reindeer));
    newDeer->flyTime = atoi(parts[6]);
    newDeer->restTime = atoi(parts[13]);
    newDeer->flyCounter = newDeer->flyTime;
    newDeer->restCounter = newDeer->restTime;
    newDeer->speed = atoi(parts[3]);
    newDeer->isFlying = true;
    newDeer->distance = 0;
    newDeer->points = 0;
    
    reindeers[i] = newDeer;
    free(parts);
  }

  return reindeers;
}


int getMostValue(Reindeer** reindeers, int size, bool doDistance){
  int best = 0;
  for (int i =0; i < size; i++){
    if (doDistance){
      if (reindeers[i]->distance > best){
        best = reindeers[i]->distance;
      }
    } else {
      if (reindeers[i]->points > best){
        best = reindeers[i]->points;
      }
    }
  }
  return best;
}

int getBestReindeer(Reindeer** reindeers, int size, int seconds){
  for (int i = 0; i < seconds; i++){
    for (int j = 0; j < size; j++){
      if (reindeers[j]->isFlying){
        reindeers[j]->distance+= reindeers[j]->speed;
        reindeers[j]->flyCounter--;
        if (reindeers[j]->flyCounter <= 0){
          reindeers[j]->isFlying = false;
          reindeers[j]->flyCounter = reindeers[j]->flyTime;
        }
      } else {
        reindeers[j]->restCounter--;
        if (reindeers[j]->restCounter <= 0){
          reindeers[j]->isFlying = true;
          reindeers[j]->restCounter = reindeers[j]->restTime;
        }
      }
    }
    int best = getMostValue(reindeers, size, true);
    for (int j = 0; j < size; j++){
      if (reindeers[j]->distance == best){
        reindeers[j]->points++;
      }
    }
  }
  return getMostValue(reindeers, size, true);
}