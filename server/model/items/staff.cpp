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

void Staff::special_use(Hero *hero) {
  if (hero->current_mana < mana_consumption)
    throw ModelException("Mana insuficiente para utilizar la especial!", "10");
  hero->set_hp(hero->current_hp + hp_regen);
  hero->current_mana -= mana_consumption;
}

void Staff::use(Hero *hero) {
  hero->unequip_staff();
  hero->equip_staff(this->id);
  // hero->current_hp = std::min(hero->current_hp + hp_regen, hero->max_hp);
  // hero->current_mana -= mana_consumption;
}