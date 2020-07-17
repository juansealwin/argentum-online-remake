#include "weapon.h"
#include "item.h"
Weapon::Weapon(int id, unsigned int min_damage, unsigned int max_damage,
               unsigned int range)
    : Item(id), min_damage(min_damage), max_damage(max_damage), range(range) {}

void Weapon::use(Hero *hero) {
  hero->unequip_weapon();
  hero->equip_weapon(this->id);
}

//void Weapon::attack_use(Hero *hero) {}

Weapon::~Weapon() {}
