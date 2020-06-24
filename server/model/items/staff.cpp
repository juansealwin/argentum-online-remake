#include "staff.h"

Staff::Staff(int id, unsigned int min_damage, unsigned int max_damage,
             unsigned int range, unsigned int mana_consumption,
             unsigned int hp_regen)
    : Weapon(id, min_damage, max_damage, range),
      mana_consumption(mana_consumption),
      hp_regen(hp_regen) {}

Staff::~Staff() {}

bool Staff::can_be_used_by(Hero *hero) {
  return hero->current_mana >= mana_consumption;
}

void Staff::use(Hero *hero) {
  hero->current_hp += hp_regen;
  if (hero->current_hp >= hero->max_hp) hero->current_hp = hero->max_hp;
  hero->current_mana -= mana_consumption;
}