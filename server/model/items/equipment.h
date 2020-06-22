#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "defensive_item.h"
#include "staff.h"
#include "weapon.h"
class Equipment {
 public:
  Equipment(Weapon *weapon, Staff *staff, DefensiveItem *helmet,
            DefensiveItem *armour, DefensiveItem *shield);
  ~Equipment();
  Equipment(const Equipment &) = delete;
  //PRE: Se debe llamar a unequip_x antes de equipar, si no
  //se perdera memoria!
  void equip_weapon(Weapon *weapon);
  void equip_staff(Staff *staff);
  void equip_shield(DefensiveItem *shield);
  void equip_helmet(DefensiveItem *helmet);
  void equip_armour(DefensiveItem *armour);
  Weapon* unequip_weapon();
  Staff* unequip_staff();
  DefensiveItem* unequip_shield();
  DefensiveItem* unequip_helmet();
  DefensiveItem* unequip_armour();

  Weapon *weapon = nullptr;
  Staff *staff = nullptr;
  DefensiveItem *helmet = nullptr;
  DefensiveItem *armour = nullptr;
  DefensiveItem *shield = nullptr;
};
#endif  // EQUIPMENT_H
