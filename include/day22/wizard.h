#ifndef WIZARD_H
#define WIZARD_H


#define SPELLS 5
#define SHIELD 113
typedef struct character {
  int hp;
  int damage;
  int mana;
  int spent;
} Character;

typedef struct spell {
  int cost;
  int duration;
  int damage;
  int healing;
  int armor;
  int mana;
  bool next;
} Spell;

Spell** createSpells(void);
Character* createBoss(char* input);
int doFight(bool hard, Character* player, Character* boss, Spell** spells);
void findSpentMana(bool hard, Spell** spells, Character* player, Character* boss, Spell* spell, Spell** curr, int* min);


#endif