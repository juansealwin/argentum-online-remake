#include "hero.h"

#include "defensive_item.h"
#include "staff.h"
#include "weapon.h"

Hero::Hero(int x, int y, unsigned int race_id, char repr, unsigned int level, unsigned int strength,
           unsigned int intelligence, unsigned int agility, unsigned int constitution, unsigned int f_class_hp,
           unsigned int f_race_hp, unsigned int f_race_recovery, unsigned int f_race_mana,
           unsigned int f_class_mana, unsigned int f_class_meditation, unsigned int gold, unsigned int class_id,
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
  if (!alive) return;
  current_hp = std::min(current_hp + f_race_recovery, max_hp);
  if (!meditating)
    current_mana = std::min(current_mana + f_race_recovery, max_mana);
  else
    current_mana =
        std::min(current_mana + (f_class_meditation * intelligence), max_mana);
}

void Hero::equip_weapon(unsigned int weapon_id) {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(weapon_id)) {
    Item *w = inventory->remove_item(weapon_id);
    equipment->equip_weapon(dynamic_cast<Weapon *>(w));
  }
}
void Hero::equip_staff(unsigned int staff_id) {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(staff_id)) {
    Item *w = inventory->remove_item(staff_id);
    equipment->equip_staff(dynamic_cast<Staff *>(w));
  }
}
void Hero::equip_shield(unsigned int shield_id) {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(shield_id)) {
    Item *w = inventory->remove_item(shield_id);
    equipment->equip_shield(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::equip_helmet(unsigned int helmet_id) {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(helmet_id)) {
    Item *w = inventory->remove_item(helmet_id);
    equipment->equip_helmet(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::equip_armour(unsigned int armour_id) {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(armour_id)) {
    Item *w = inventory->remove_item(armour_id);
    equipment->equip_armour(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::unequip_weapon() {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  Weapon *weapon = equipment->unequip_weapon();
  if (weapon) inventory->add_item(weapon);
}
void Hero::unequip_staff() {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  Staff *staff = equipment->unequip_staff();
  if (staff) inventory->add_item(staff);
}
void Hero::unequip_shield() {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  DefensiveItem *shield = equipment->unequip_shield();
  if (shield) inventory->add_item(shield);
}
void Hero::unequip_helmet() {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  DefensiveItem *helmet = equipment->unequip_helmet();
  if (helmet) inventory->add_item(helmet);
}
void Hero::unequip_armour() {
  if (!alive) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  DefensiveItem *armour = equipment->unequip_armour();
  if (armour) inventory->add_item(armour);
}

Item *Hero::remove_item(unsigned int item_id) {
  if (!alive) throw ModelException("Ghosts can't add items to inventory!", "5");
  meditating = false;
  Item *i = inventory->remove_item(item_id);
  return i;
}

void Hero::add_item(Item *item) {
  if (!alive) throw ModelException("Ghosts can't add items to inventory!", "4");
  meditating = false;
  inventory->add_item(item);
}

unsigned int Hero::damage(BaseCharacter *b) {
  if (!alive) throw ModelException("Ghosts can't attack!", "3");
  if (!close_enough(b)) throw ModelException("Too far to attack!", "7");
  if (!equipment->can_use_primary_weapon(this))
    throw ModelException("Cant use primary weapon! (not enough mana?)", "8");
  meditating = false;
  // mover a json!
  const float critical_damage_probability = 0.125;
  bool critical = false;
  unsigned int dmg = calculate_damage();
  float p = rand() / double(RAND_MAX);
  if (p < critical_damage_probability) critical = true;
  // actualizar experiencia
  return b->receive_damage(dmg, critical);
}

unsigned int Hero::receive_damage(unsigned int damage, bool critical) {
  if (!alive) throw ModelException("Can't attack ghosts!", "2");
  meditating = false;
  // meter en json!
  const float evasion = 0.001;
  int actual_damage = damage;
  float p = pow(rand() / double(RAND_MAX), agility);
  if (critical)
    actual_damage *= CRITICAL_DAMAGE_MULTIPLIER;
  else if (p < evasion) {
    actual_damage = 0;
  } else {
    actual_damage =
        std::max(damage - equipment->get_defense_bonus(), (unsigned int)0);
  }  // Hacer chequeos si esta vivo etc?
  current_hp -= actual_damage;
  if (current_hp <= 0) alive = false;
  return actual_damage;
}

void Hero::meditate() {
  if (!alive) throw ModelException("Can't meditate death!", "2");;
  meditating = true;
}

Hero::~Hero() {
  delete inventory;
  delete equipment;
}

/* private methods */

unsigned int Hero::calculate_damage() {
  return strength * equipment->get_attack_bonus();
}

bool Hero::close_enough(BaseCharacter *other) {
  unsigned int distance =
      floor(sqrt(pow(x_position - other->x_position, 2) +
                 pow(y_position - other->y_position, 2) * 1.0));
  return (((int)equipment->range() - (int)distance) >= 0);
}
