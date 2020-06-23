#include "hero.h"

#include "defensive_item.h"
#include "staff.h"
#include "weapon.h"

Hero::Hero(int x, int y, int race_id, char repr, int level, int strength,
           int intelligence, int agility, int constitution, int f_class_hp,
           int f_race_hp, int f_race_recovery, int f_race_mana,
           int f_class_mana, int f_class_meditation, int gold, int class_id,
           Map *map)
    : BaseCharacter(x, y, race_id, repr, level, map),
      strength(strength),
      intelligence(intelligence),
      agility(agility),
      constitution(constitution),
      f_class_hp(f_class_hp),
      f_race_hp(f_race_hp),
      f_race_recovery(f_race_recovery),
      f_race_mana(f_race_mana),
      f_class_mana(f_class_mana),
      f_class_meditation(f_class_meditation),
      gold(gold),
      class_id(class_id) {
  max_hp = current_hp = constitution * f_class_hp * f_race_hp * level;
  max_mana = current_mana = intelligence * f_class_mana * f_race_mana * level;
  equipment = new Equipment();
  inventory = new Inventory(INVENTORY_SIZE);
}

void Hero::update() {
  // aumento de vida, mana, etc.
  // std::cout << "Updating hero: not implemented" << std::endl;
}

void Hero::equip_weapon(unsigned int weapon_id) {
  if (inventory->has_item(weapon_id)) {
    Item *w = inventory->remove_item(weapon_id);
    equipment->equip_weapon(dynamic_cast<Weapon *>(w));
  }
}
void Hero::equip_staff(unsigned int staff_id) {
  if (inventory->has_item(staff_id)) {
    Item *w = inventory->remove_item(staff_id);
    equipment->equip_staff(dynamic_cast<Staff *>(w));
  }
}
void Hero::equip_shield(unsigned int shield_id) {
  if (inventory->has_item(shield_id)) {
    Item *w = inventory->remove_item(shield_id);
    equipment->equip_shield(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::equip_helmet(unsigned int helmet_id) {
  if (inventory->has_item(helmet_id)) {
    Item *w = inventory->remove_item(helmet_id);
    equipment->equip_helmet(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::equip_armour(unsigned int armour_id) {
  if (inventory->has_item(armour_id)) {
    Item *w = inventory->remove_item(armour_id);
    equipment->equip_armour(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::unequip_weapon() {
  Weapon *weapon = equipment->unequip_weapon();
  if (weapon) inventory->add_item(weapon);
}
void Hero::unequip_staff() {
  Staff *staff = equipment->unequip_staff();
  if (staff) inventory->add_item(staff);
}
void Hero::unequip_shield() {
  DefensiveItem *shield = equipment->unequip_shield();
  if (shield) inventory->add_item(shield);
}
void Hero::unequip_helmet() {
  DefensiveItem *helmet = equipment->unequip_helmet();
  if (helmet) inventory->add_item(helmet);
}
void Hero::unequip_armour() {
  DefensiveItem *armour = equipment->unequip_armour();
  if (armour) inventory->add_item(armour);
}

Item * Hero::remove_item(unsigned int item_id) {
  Item *i = inventory->remove_item(item_id);
  return i;
}

void Hero::add_item(Item *item) {
  inventory->add_item(item);
}

int Hero::damage(Hero *other) {  // deberia cambiarlo por un baseCharacter ya
                                 // que puedo atacar a monstruos
  int dmg = strength;            //+ sumar lo de los items
  // actualizar experiencia
  return other->receive_damage(dmg, false);
}
// devuelve el dano que efectivamente recibi
int Hero::receive_damage(int damage, bool critical) {
  int actual_damage = damage;
  if (critical)
    actual_damage *= CRITICAL_DAMAGE_MULTIPLIER;
  else {  // esquivar si rand(0,1) ** agilidad < 0.001
    // si no se pudo esquivar:
    // defensa = rand(armaduramin,armaduramax) + rand(cascomin,cascomas) +
    // rand(cascomin,cascomax)
    int defense = 0;
    actual_damage -= defense;
  }  // Hacer chequeos si esta vivo etc?
  return actual_damage;
}

Hero::~Hero() {}