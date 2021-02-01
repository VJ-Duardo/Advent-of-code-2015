#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "day21/rpg.h"
#include "utils/utils.h"


int main(void){
  char* itemInput = getFileContent((char*)"src/day21/items.txt");
  int itemCount = 0;
  
  Item** items = createItems(itemInput, &itemCount);
  Item*** itemTypes = createItemLists(items);
  int sizes[] = {5, 6, 7, 7};

  char* input = getFileContent((char*)"src/day21/boss.txt");
  Character* boss = createBoss(input);
  
  int result = 1000;
  getSeekedWin(itemTypes, sizes, boss, 0, 0, 0, 4, &result, true);
  printf("%d\n", result);

  result = 0;
  getSeekedWin(itemTypes, sizes, boss, 0, 0, 0, 4, &result, false);
  printf("%d\n", result);

  return 0;
}


void getSeekedWin(Item*** items, int* sizes, Character* boss, int currDmg, int currArm, int currCost, int curr, int* result, bool min){
  if (curr == 0){
    Character player = {.hp=100, .damage=currDmg, .armor=currArm};
    bool r = doFight(&player, boss);
    if (r && min){
      if (currCost < *result){
        *result = currCost;
      }
    } else if (!r && !min){
      if (currCost > *result){
        *result = currCost;
      }
    }
    return;
  }
  int j = 4-curr;
  for (int i=0; i< sizes[j]; i++){
    getSeekedWin(items, sizes, boss, currDmg+items[j][i]->damage, currArm+items[j][i]->armor, currCost+items[j][i]->cost, curr-1, result, min);
  }
}


bool doFight(Character* player, Character* boss){
  int playerHP = player->hp, bossHP = boss->hp;
  int playerDamage = (player->damage - boss->armor <= 0) ? 1 : player->damage-boss->armor;
  int bossDamage = (boss->damage - player->armor <= 0) ? 1 : boss->damage-player->armor;
  bool playerTurn = true;
  while (playerHP > 0 && bossHP > 0){
    if (playerTurn){
      bossHP -= playerDamage;
    } else{
      playerHP -= bossDamage;
    }
    playerTurn = !playerTurn;
  }
  return playerHP > 0;
}



Character* createBoss(char* input){
  int partsSize = 0;
  char** parts = getSplitArray(input, "\n ", &partsSize);

  Character* boss = (Character*) malloc(sizeof(Character));
  boss->hp = atoi(parts[2]);
  boss->damage = atoi(parts[4]);
  boss->armor = atoi(parts[6]);

  for (int i=0; i < partsSize;free(parts[i++]));
  free(parts);
  
  return boss;
}


Item*** createItemLists(Item** items){
  Item* empty = (Item*) malloc(sizeof(Item));
  empty-> cost = 0;
  empty-> damage = 0;
  empty-> armor = 0;

  Item*** itemTypes = (Item***) malloc(4*sizeof(Item**));

  Item** weapons = (Item**) malloc(5*sizeof(Item*));
  memcpy(weapons, &items[0], 5*sizeof(Item*));
  itemTypes[0] = weapons;
  
  Item** armor = (Item**) malloc((5+1)*sizeof(Item*));
  armor[0] = empty;
  memcpy(armor+1, &items[5], 5*sizeof(Item*));
  itemTypes[1] = armor;

  Item** rings = (Item**) malloc((6+1)*sizeof(Item*));
  rings[0] = empty;
  memcpy(rings+1, &items[10], 6*sizeof(Item*));
  itemTypes[2] = rings;
  itemTypes[3] = rings;

  free(items);
  return itemTypes;
}


Item** createItems(char* input, int* itemCount){
  Item** items = (Item**) NULL;

  int lineCount = 0;
  char** lines = getSplitArray(input, "\n", &lineCount);
  
  for (int i=1; i < lineCount; i++){
    if (i != 6 && i != 12){
      int partCount = 0;
      char** lineParts = getSplitArray(lines[i], " ", &partCount);
      
      Item* item = (Item*) malloc(sizeof(Item));
      item->cost = atoi(lineParts[(partCount<5)?1:2]);
      item->damage = atoi(lineParts[(partCount<5)?2:3]);
      item->armor = atoi(lineParts[(partCount<5)?3:4]);
      items = realloc(items, ((*itemCount)+1)*sizeof(Item*));
      items[(*itemCount)++] = item;

      for (int j=0; j <partCount; free(lineParts[j++]));
      free(lineParts);
    }
    free(lines[i]);
  }
  free(lines);
  free(input);

  return items;
}