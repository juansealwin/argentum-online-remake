#include "base_character.h"
#include "stdint.h"
#ifndef HERO_H
#define HERO_H

class Hero : public BaseCharacter {
 public:
  Hero(int x, int y, int type, char repr, int level, int strength,
       int intelligence, int agility, int constitution, int base_mana,
       int f_class_hp, int f_race_hp, int f_race_recovery, int f_race_mana,
       int f_class_mana, int f_class_meditation, int gold);
  virtual ~Hero();
  Hero(const Hero &) = delete;
 private:
  int strength;
  int intelligence;
  int agility;
  int constitution;
  int base_mana;
  int f_class_hp;
  int f_race_hp;
  int f_race_recovery;
  int f_race_mana;
  int f_class_mana;
  int f_class_meditation;
  int gold;
};
#endif  // HERO_H
