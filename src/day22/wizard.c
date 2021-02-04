#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "day22/wizard.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day22/boss.txt");
  Character* boss = createBoss(input);

  Character* player = (Character*) malloc(sizeof(Character));
  player->hp = 50;
  player->damage = 0;
  player->mana = 500;
  player->spent = 0;

  Spell** spells = createSpells();
  
  int result = -1;
  Spell* currSpells[SPELLS];
  for (int i=0; i <SPELLS; currSpells[i++] = (Spell*)NULL);
  findSpentMana(false, spells, player, boss, spells[5], currSpells, &result);
  printf("%d\n", result);

  result = -1;
  findSpentMana(true, spells, player, boss, spells[5], currSpells, &result);
  printf("%d\n", result);

  return 0;
}


static bool spellInUse(Spell** currSpells, Spell* spell){
  for (int i=0; i < SPELLS; i++){
    if (currSpells[i] != NULL && currSpells[i]->cost == spell->cost && currSpells[i]->duration > 1){
      return true;
    }
  }
  return false;
}

static void addSpell(Spell** currSpells, Spell* spell){
  for (int i=0; i < SPELLS; i++){
    if (currSpells[i] == NULL){
      currSpells[i] = spell;
      return;
    }
  }
}

static void freeCurr(Spell** currSpells){
  for (int i=0; i < SPELLS; i++){
    if (currSpells[i] != NULL){
      free(currSpells[i]);
    }
  }
  free(currSpells);
}


void findSpentMana(bool hard, Spell** spells, Character* player, Character* boss, Spell* spell, Spell** curr, int* min){
  if (spell->cost > player->mana || spellInUse(curr, spell)){
    return;
  }
  Character* playerCopy = (Character*) malloc(sizeof(Character));
  memcpy(playerCopy, player, sizeof(Character));
  playerCopy->spent+= spell->cost;
  playerCopy->mana-= spell->cost;

  Character* bossCopy = (Character*) malloc(sizeof(Character));
  memcpy(bossCopy, boss, sizeof(Character));

  Spell* spellCopy = (Spell*) malloc(sizeof(Spell));
  memcpy(spellCopy, spell, sizeof(Spell));

  Spell** currCopy = (Spell**) malloc(SPELLS*sizeof(Spell*));
  for (int i=0; i < SPELLS; i++){
    if (curr[i] != NULL){
      Spell* spellCpy = (Spell*) malloc(sizeof(Spell));
      memcpy(spellCpy, curr[i], sizeof(Spell));
      currCopy[i] = spellCpy;
    } else {
      currCopy[i] = NULL;
    }
  }
  addSpell(currCopy, spellCopy);
  
  if (spell->cost){
    int r = doFight(hard, playerCopy, bossCopy, currCopy);
    if (r != -1){
      if (r == 1 && (playerCopy->spent < *min || *min == -1)){
        *min = playerCopy->spent;
      }
      free(playerCopy);
      free(bossCopy);
      freeCurr(currCopy);
      return;
    }
  }

  for (int i=0; i < SPELLS; i++){
    findSpentMana(hard, spells, playerCopy, bossCopy, spells[i], currCopy, min);
  }
  free(playerCopy);
  free(bossCopy);
  freeCurr(currCopy);
}


int doFight(bool hard, Character* player, Character* boss, Spell** spells){
  if (hard && (player->hp--)-1 < 1){
    return 0;
  }

  for (int i=0; i<SPELLS; i++){
    if(spells[i] == NULL){continue;}
    if (spells[i]->next){
      spells[i]->next = false;
      continue;
    }
    boss->hp -= spells[i]->damage;
    player->mana += spells[i]->mana;
    player->hp += spells[i]->healing;
    spells[i]->duration--;
    if (spells[i]->duration == 0){
      free(spells[i]);
      spells[i] = NULL;
    }
  }
  if (boss->hp < 1){
    return 1;
  }

  int shield = 0;
  for (int i=0; i<SPELLS; i++){
    if(spells[i] == NULL){continue;}
    boss->hp -= spells[i]->damage;
    player->mana += spells[i]->mana;
    if (boss->hp < 1){
      return 1;
    }
    if (spells[i]->cost == SHIELD){
      shield = spells[i]->armor;
    }
    spells[i]->duration--;
    if (spells[i]->duration == 0){
      free(spells[i]);
      spells[i] = NULL;
    }
  }

  int damage = boss->damage - shield;
  player->hp -= (damage < 1) ? 1 : damage;
  if (player->hp < 1){
    return 0;
  }

  return -1;
}


static Spell* createSpell(int cst, int drtn, int dmg, int hlng, int armr, int mna, bool nxt){
  Spell* spell = (Spell*) malloc(sizeof(Spell));
  spell->cost = cst;
  spell->duration = drtn;
  spell->damage = dmg;
  spell->healing = hlng;
  spell->armor = armr;
  spell->mana = mna;
  spell->next = nxt;
  return spell;
}

Spell** createSpells(void){
  Spell** spells = (Spell**) malloc((SPELLS+1)*sizeof(Spell*));
  spells[0] = createSpell(53, 1, 4, 0, 0, 0, false);
  spells[1] = createSpell(73, 1, 2, 2, 0, 0, false);
  spells[2] = createSpell(113, 6, 0, 0, 7, 0, true);
  spells[3] = createSpell(173, 6, 3, 0, 0, 0, true);
  spells[4] = createSpell(229, 5, 0, 0, 0, 101, true);
  spells[5] = createSpell(0, 1, 0, 0, 0, 0, false);
  return spells;
}


Character* createBoss(char* input){
  int partsSize = 0;
  char** parts = getSplitArray(input, "\n ", &partsSize);

  Character* boss = (Character*) malloc(sizeof(Character));
  boss->hp = atoi(parts[2]);
  boss->damage = atoi(parts[4]);
  boss->mana = -1;
  boss->spent = -1;

  for (int i=0; i < partsSize;free(parts[i++]));
  free(parts);
  free(input);
  
  return boss;
}