#ifndef OLYMPICS_H
#define OLYMPICS_H

#include <stdbool.h>


typedef struct reindeer {
  int flyTime;
  int restTime;
  int flyCounter;
  int restCounter;
  int speed;
  int distance;
  int points;
  bool isFlying;
} Reindeer;

Reindeer** createReindeers(char** lines, int size);
int getBestReindeer(Reindeer** reindeers, int size, int seconds);
int getMostValue(Reindeer** reindeers, int size, bool doDistance);


#endif