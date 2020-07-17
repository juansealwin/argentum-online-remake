#include "weapon.h"
#include "item.h"
#include "staff.h"
Weapon::Weapon(int id, unsigned int min_damage, unsigned int max_damage,
               unsigned int range)
    : Item(id), min_damage(min_damage), max_damage(max_damage), range(range) {}

void Weapon::use(Hero *hero) {
  Item *equipped_item = nullptr;
  if(hero->equipment->has_staff()) {
    equipped_item = hero->equipment->unequip_staff();
  } else if (hero->equipment->has_weapon()) {
    equipped_item = hero->equipment->unequip_weapon();
  }
  //hero->unequip_weapon();
  //hero->unequip_staff();
  hero->equip_weapon(this->id);
  if(equipped_item) hero->add_item(equipped_item);
}

//void Weapon::attack_use(Hero *hero) {}

Weapon::~Weapon() {}
