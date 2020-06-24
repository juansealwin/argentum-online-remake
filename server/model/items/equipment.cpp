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
  }
  else if (staff) {
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
  if (weapon) range = weapon->range;
  else if (staff) range = staff->range;
  return range;
}

void Equipment::equip_weapon(Weapon *weapon) { this->weapon = weapon; }

void Equipment::equip_staff(Staff *staff) { this->staff = staff; }

void Equipment::equip_shield(DefensiveItem *shield) { this->shield = shield; }

void Equipment::equip_helmet(DefensiveItem *helmet) { this->helmet = helmet; }

void Equipment::equip_armour(DefensiveItem *armour) { this->armour = armour; }

Weapon *Equipment::unequip_weapon() { return weapon; }

Staff *Equipment::unequip_staff() { return staff; }

DefensiveItem *Equipment::unequip_shield() { return shield; }

DefensiveItem *Equipment::unequip_helmet() { return helmet; }

DefensiveItem *Equipment::unequip_armour() { return armour; }
