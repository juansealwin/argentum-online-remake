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
  unsigned int bonus = 1;
  if (weapon) {
    bonus = HelperFunctions::random_int(weapon->min_damage, weapon->max_damage);
  } else if (staff) {
    bonus = HelperFunctions::random_int(staff->min_damage, staff->max_damage);
  }
  return bonus;
}

unsigned int Equipment::get_defense_bonus() {
  unsigned int bonus = 0;
  if (helmet) {
    bonus = HelperFunctions::random_int(helmet->min_defense, helmet->max_defense);
  }
  if (armour) {
    bonus = HelperFunctions::random_int(armour->min_defense, armour->max_defense);
  }
  if (shield) {
    bonus = HelperFunctions::random_int(shield->min_defense, shield->max_defense);
  }
  return bonus;
}

unsigned int Equipment::range() {
  unsigned int range = 1;
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

void Equipment::equip_weapon(Weapon *weapon) {
  if (staff)
    throw ModelException("Can't equip weapon if you are using a staff!", "10");
  this->weapon = weapon;
}

void Equipment::equip_staff(Staff *staff) {
  if (weapon)
    throw ModelException("Can't equip staff if you are using a weapon!", "10");
  this->staff = staff;
}

void Equipment::equip_shield(DefensiveItem *shield) { this->shield = shield; }

void Equipment::equip_helmet(DefensiveItem *helmet) { this->helmet = helmet; }

void Equipment::equip_armour(DefensiveItem *armour) { 
  this->armour = armour;
  if(this->armour) std::cout << "succesfully set this->armour, the id is " << this->armour->id << std::endl;
  }

Weapon *Equipment::unequip_weapon() {
  Weapon *w = weapon;
  weapon = nullptr;
  return w;
}
Item *Equipment::unequip(unsigned int item_id) {
  Item *i = nullptr;
  if (staff)
    if (staff->id == item_id) {
      i = staff;
      staff = nullptr;
    }
  if (weapon)
    if (weapon->id == item_id) {
      i = weapon;
      weapon = nullptr;
    }
  if (armour)
    if (armour->id == item_id) {
      i = armour;
      armour = nullptr;
    }
  if (helmet)
    if (helmet->id == item_id) {
      i = helmet;
      helmet = nullptr;
    }
  if (shield)
    if (shield->id == item_id) {
      i = shield;
      shield = nullptr;
    }
  return i;
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

unsigned int Equipment::primary_weapon_id() {
  unsigned int id = fist;
  if (weapon)
    id = weapon->id;
  else if (staff)
    id = staff->id;
  return id;
}

uint8_t Equipment::count() {
  uint8_t count = 0;
  if (weapon) count++;
  if (staff) count++;
  if (shield) count++;
  if (helmet) count++;
  if (armour) count++;
  return count;
}

bool Equipment::can_hold_weapon() {
  return (!staff);
}
bool Equipment::can_hold_staff() {
  return (!weapon);
}

bool Equipment::has_weapon() {
  return weapon;
}
bool Equipment::has_staff() {
  return staff;
}
bool Equipment::has_helmet() {
  return helmet;
}
bool Equipment::has_armour() {
  return armour;
}
bool Equipment::has_shield() {
  return shield;
}