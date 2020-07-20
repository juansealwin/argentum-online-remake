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
    throw ModelException("Mana insuficiente para utilizar la especial!");
  if (hp_regen == 0) return;
  hero->set_hp(hero->current_hp + hp_regen);
  hero->set_mana(hero->current_mana - mana_consumption);
  hero->affected_by = this->id;
}

void Staff::attack_use(Hero *hero) {
  if (hero->current_mana < mana_consumption)
    throw ModelException("Mana insuficiente!");
  hero->set_hp(hero->current_hp + hp_regen);
  hero->set_mana(hero->current_mana - mana_consumption);
  //hero->current_mana -= mana_consumption;
}

void Staff::use(Hero *hero) {
    Item *equipped_item = nullptr;
  if(hero->equipment->has_staff()) {
    equipped_item = hero->equipment->unequip_staff();
  } else if (hero->equipment->has_weapon()) {
    equipped_item = hero->equipment->unequip_weapon();
  }

  //hero->unequip_staff();
  //hero->unequip_weapon();
  hero->equip_staff(this->id);
  if(equipped_item) hero->add_item(equipped_item);
}