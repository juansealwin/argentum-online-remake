#include "equipment.h"

#include "defensive_item.h"
#include "staff.h"
#include "weapon.h"
Equipment::Equipment(Weapon *weapon, Staff *staff, DefensiveItem *helmet,
                     DefensiveItem *armour, DefensiveItem *shield)
    : weapon(weapon),
      staff(staff),
      helmet(helmet),
      armour(armour),
      shield(shield) {}

Equipment::Equipment() {}

Equipment::~Equipment() {
  if (weapon) delete weapon;
  if (staff) delete staff;
  if (shield) delete shield;
  if (helmet) delete helmet;
  if (armour) delete armour;
}

unsigned int Equipment::get_attack_bonus() {
  unsigned int bonus = 0;
  if (weapon) {
    bonus = rand() % (weapon->max_damage - weapon->min_damage + 1) +
            weapon->min_damage;
  } else if (staff) {
    bonus = rand() % (staff->max_damage - staff->min_damage + 1) +
            staff->min_damage;
  }
  return bonus;
}

unsigned int Equipment::get_defense_bonus() {
  unsigned int bonus = 0;
  if (helmet) {
    bonus += rand() % (helmet->max_defense - helmet->min_defense + 1) +
             helmet->min_defense;
  }
  if (armour) {
    bonus += rand() % (armour->max_defense - armour->min_defense + 1) +
             armour->min_defense;
  }
  if (shield) {
    bonus += rand() % (shield->max_defense - shield->min_defense + 1) +
             shield->min_defense;
  }
  return bonus;
}

unsigned int Equipment::range() {
  unsigned int range = 0;
  if (weapon)
    range = weapon->range;
  else if (staff)
    range = staff->range;
  return range;
}

bool Equipment::can_use_primary_weapon(Hero *hero) {
  if (weapon)
    return weapon->can_be_used_by(hero);
  else if (staff)
    return staff->can_be_used_by(hero);
  return false;
}

void Equipment::use_primary_weapon(Hero *hero) {
  if (weapon)
    weapon->use(hero);
  else if (staff)
    weapon->use(hero);
}

void Equipment::equip_weapon(Weapon *weapon) { this->weapon = weapon; }

void Equipment::equip_staff(Staff *staff) { this->staff = staff; }

void Equipment::equip_shield(DefensiveItem *shield) { this->shield = shield; }

void Equipment::equip_helmet(DefensiveItem *helmet) { this->helmet = helmet; }

void Equipment::equip_armour(DefensiveItem *armour) { this->armour = armour; }

Weapon *Equipment::unequip_weapon() {
  Weapon *w = weapon;
  weapon = nullptr;
  return w;
}

Staff *Equipment::unequip_staff() {
  Staff *s = staff;
  staff = nullptr;
  return s;
}

DefensiveItem *Equipment::unequip_shield() {
  DefensiveItem *s = shield;
  shield = nullptr;
  return s;
}

DefensiveItem *Equipment::unequip_helmet() {
  DefensiveItem *h = helmet;
  helmet = nullptr;
  return h;
}

DefensiveItem *Equipment::unequip_armour() {
  DefensiveItem *a = armour;
  armour = nullptr;
  return a;
}
