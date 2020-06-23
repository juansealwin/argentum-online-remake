#include "equipment.h"
Equipment::Equipment(Weapon *weapon, Staff *staff, DefensiveItem *helmet,
                     DefensiveItem *armour, DefensiveItem *shield)
    : weapon(weapon),
      staff(staff),
      helmet(helmet),
      armour(armour),
      shield(shield) {}

Equipment::Equipment() {
  if (weapon) delete weapon;
  if (staff) delete staff;
  if (shield) delete shield;
  if (helmet) delete helmet;
  if (armour) delete armour;
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
