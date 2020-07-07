#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <cstdint>
class Weapon;
class DefensiveItem;
class Staff;
class Hero;
class Item;
class Equipment {
 public:
  // constructores de equipamiento vacio o con items
  Equipment(Weapon *weapon, Staff *staff, DefensiveItem *helmet,
            DefensiveItem *armour, DefensiveItem *shield);
  Equipment();
  ~Equipment();
  Equipment(const Equipment &) = delete;
  bool has_weapon();
  bool has_staff();
  bool has_helmet();
  bool has_armour();
  bool has_shield();
  // PRE: Se debe llamar a unequip_x antes de equipar, si no,
  // se perdera memoria
  bool can_hold_weapon();
  bool can_hold_staff();
  void equip_weapon(Weapon *weapon);
  void equip_staff(Staff *staff);
  void equip_shield(DefensiveItem *shield);
  void equip_helmet(DefensiveItem *helmet);
  void equip_armour(DefensiveItem *armour);
  // devuelve distancia a la cual puede llegar a atacar
  unsigned int range();
  bool can_use_primary_weapon(Hero *hero);
  void use_primary_weapon(Hero *hero);
  Weapon *unequip_weapon();
  Staff *unequip_staff();
  DefensiveItem *unequip_shield();
  DefensiveItem *unequip_helmet();
  DefensiveItem *unequip_armour();
  Item *unequip(unsigned int item_id);
  unsigned int get_attack_bonus();
  unsigned int get_defense_bonus();
  unsigned int primary_weapon_id();
  //devuelve cantidad de items equipados
  uint8_t count();
  Weapon *weapon = nullptr;
  Staff *staff = nullptr;
  DefensiveItem *helmet = nullptr;
  DefensiveItem *armour = nullptr;
  DefensiveItem *shield = nullptr;
};
#endif  // EQUIPMENT_H
