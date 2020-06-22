#include "base_character.h"
#include "stdint.h"
#ifndef HERO_H
#define HERO_H
#define CRITICAL_DAMAGE_MULTIPLIER 2
class Hero : public BaseCharacter {
 public:
  Hero(int x, int y, int race_id, char repr, int level, int strength,
       int intelligence, int agility, int constitution, int f_class_hp,
       int f_race_hp, int f_race_recovery, int f_race_mana, int f_class_mana,
       int f_class_meditation, int gold, int class_id, Map *map);
  // devuelve el dano causado
  void update() override;
  int damage(Hero *other);
  // devuelve el dano que efectivamente recibi
  int receive_damage(int damage, bool critical);
  virtual ~Hero();
  Hero(const Hero &) = delete;
  friend class Staff;
  int current_mana;
  int max_mana;

 private:
  int strength;
  int intelligence;
  int agility;
  int constitution;
  int f_class_hp;
  int f_race_hp;
  int f_race_recovery;
  int f_race_mana;
  int f_class_mana;
  int f_class_meditation;
  int gold;
  int class_id;
};
#endif  // HERO_H
