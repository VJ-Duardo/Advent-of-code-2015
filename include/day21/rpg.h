#ifndef RPG_H
#define RPG_H


typedef struct item {
  int cost;
  int damage;
  int armor;
} Item;

typedef struct character {
  int hp;
  int damage;
  int armor;
  int cost;
} Character;

Item** createItems(char* input, int* itemCount);
Item*** createItemLists(Item** items);
bool doFight(Character* player, Character* boss);
Character* createBoss(char* input);
void getSeekedWin(Item*** items, int* sizes, Character* boss, int currDmg, int currArm, int currCost, int curr, int* result, bool min);


#endif