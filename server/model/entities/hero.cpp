#include "hero.h"

#include "defensive_item.h"
#include "drop.h"
#include "staff.h"
#include "weapon.h"

Hero::Hero(
    unsigned int unique_id, int x, int y, unsigned int race_id, char repr,
    unsigned int level, unsigned int strength, unsigned int intelligence,
    unsigned int agility, unsigned int constitution, unsigned int f_class_hp,
    unsigned int f_race_hp, unsigned int f_race_recovery,
    unsigned int f_race_mana, unsigned int f_class_mana,
    unsigned int f_class_meditation, unsigned int gold, unsigned int class_id,
    Map *map, std::string name, const float critical_damage_multiplier,
    const unsigned int inventory_size, const float critical_damage_probability,
    const float evasion_probability, const float max_safe_gold_multiplier,
    const float level_up_limit_power, const float starting_xp_cap,
    const unsigned int bank_size)
    : BaseCharacter(unique_id, x, y, race_id, repr, level, map, name),
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
      // gold(gold),
      class_id(class_id),
      experience(0),
      meditating(false),
      ghost_mode(false),
      name(name),
      critical_damage_multiplier(critical_damage_multiplier),
      critical_damage_probability(critical_damage_probability),
      evasion_probability(evasion_probability),
      max_safe_gold_multiplier(max_safe_gold_multiplier),
      level_up_limit_power(level_up_limit_power),
      starting_xp_cap(starting_xp_cap) {
  level_up();
  equipment = new Equipment();
  inventory = new Inventory(inventory_size, gold);
  bank = new Inventory(bank_size, 0);
}

// Hero::Hero(Hero *h, Map &map)
//     : BaseCharacter(h->unique_id, h->x_position, h->y_position, h->type, 'h',
//                     h->level, map),
//       strength(h->strength),
//       intelligence(h->intelligence),
//       agility(h->agility),
//       constitution(h->constitution),
//       f_class_hp(h->f_class_hp),
//       f_race_hp(h->f_race_hp),
//       f_race_recovery(h->f_race_recovery),
//       f_race_mana(h->f_race_mana),
//       f_class_mana(h->f_class_mana),
//       f_class_meditation(h->f_class_meditation),
//       gold(h->gold),
//       class_id(h->class_id),
//       experience(h->experience),
//       meditating(h->meditating),
//       ghost_mode(h->ghost_mode),
//       name(h->name),
//       critical_damage_multiplier(h->critical_damage_multiplier),
//       inventory_size(h->inventory_size),
//       critical_damage_probability(h->critical_damage_probability),
//       evasion_probability(h->evasion_probability),
//       max_safe_gold_multiplier(h->max_safe_gold_multiplier),
//       inventory(h->inventory),
//       equipment(h->equipment),
//       level_up_limit_power(h->level_up_limit_power),
//       starting_xp_cap(h->starting_xp_cap) {
//         h->inventory = nullptr;
//         h->equipment = nullptr;
//       }

void Hero::regenerate() {
  if (ghost_mode) return;
  current_hp = std::min(current_hp + f_race_recovery, max_hp);
  if (!meditating)
    current_mana = std::min(current_mana + f_race_recovery, max_mana);
  else
    current_mana =
        std::min(current_mana + (f_class_meditation * intelligence), max_mana);
}

void Hero::equip_weapon(unsigned int weapon_id) {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(weapon_id) && equipment->can_hold_weapon()) {
    Item *w = inventory->remove_item(weapon_id);
    equipment->equip_weapon(dynamic_cast<Weapon *>(w));
  }
}
void Hero::equip_staff(unsigned int staff_id) {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(staff_id) && equipment->can_hold_staff()) {
    Item *w = inventory->remove_item(staff_id);
    equipment->equip_staff(dynamic_cast<Staff *>(w));
  }
}
void Hero::equip_shield(unsigned int shield_id) {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(shield_id)) {
    Item *w = inventory->remove_item(shield_id);
    equipment->equip_shield(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::equip_helmet(unsigned int helmet_id) {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(helmet_id)) {
    Item *w = inventory->remove_item(helmet_id);
    equipment->equip_helmet(dynamic_cast<DefensiveItem *>(w));
  }
}
void Hero::equip_armour(unsigned int armour_id) {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  meditating = false;
  if (inventory->has_item(armour_id)) {
    Item *w = inventory->remove_item(armour_id);
    equipment->equip_armour(dynamic_cast<DefensiveItem *>(w));
  }
}

void Hero::unequip(unsigned int item_id) {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  if (inventory->is_full()) throw ModelException("Inventory is full!", "6");
  meditating = false;
  Item *item = equipment->unequip(item_id);
  if (!item)
    throw ModelException("Tried to unequip item that is not equipped!", "6");
  inventory->add_item(item);
}

void Hero::unequip_weapon() {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  if (inventory->is_full() && equipment->has_weapon())
    throw ModelException("Inventory is full!", "6");
  meditating = false;
  Weapon *weapon = equipment->unequip_weapon();
  if (weapon) {
    inventory->add_item(weapon);
  }
}
void Hero::unequip_staff() {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  if (inventory->is_full() && equipment->has_staff())
    throw ModelException("Inventory is full!", "6");
  meditating = false;
  Staff *staff = equipment->unequip_staff();
  if (staff) inventory->add_item(staff);
}
void Hero::unequip_shield() {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  if (inventory->is_full() && equipment->has_shield())
    throw ModelException("Inventory is full!", "6");
  meditating = false;
  DefensiveItem *shield = equipment->unequip_shield();
  if (shield) inventory->add_item(shield);
}
void Hero::unequip_helmet() {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  if (inventory->is_full() && equipment->has_helmet())
    throw ModelException("Inventory is full!", "6");
  meditating = false;
  DefensiveItem *helmet = equipment->unequip_helmet();
  if (helmet) inventory->add_item(helmet);
}
void Hero::unequip_armour() {
  if (ghost_mode) throw ModelException("Ghosts can't unequip/equip!", "6");
  if (inventory->is_full() && equipment->has_armour())
    throw ModelException("Inventory is full!", "6");
  meditating = false;
  DefensiveItem *armour = equipment->unequip_armour();
  if (armour) inventory->add_item(armour);
}

void Hero::use_item(unsigned int item_id) {
  if (ghost_mode) throw ModelException("Ghosts can't use items!", "5");
  meditating = false;
  Item *i = inventory->item_with_id(item_id);
  i->use(this);
}

void Hero::unbank_gold(unsigned int ammount) {
  if (ghost_mode)
    throw ModelException("Ghosts can't add gold to inventory!", "5");
  meditating = false;
  if (bank->current_gold() < ammount)
    throw ModelException("Bank doesn't have that ammount of gold!", "5");
  if (gold_space_remaining() < ammount)
    throw ModelException("Can't hold that ammount of gold in inventory!", "5");
  inventory->add_gold(bank->remove_gold(ammount));
}
void Hero::bank_gold(unsigned int ammount) {
  if (ghost_mode) throw ModelException("Ghosts can't add gold to bank!", "5");
  meditating = false;
  if (inventory->current_gold() < ammount)
    throw ModelException("Inventory doesn't have that ammount of gold!", "5");
  bank->add_gold(inventory->remove_gold(ammount));
}

bool Hero::has_gold(unsigned int q) {
  return (inventory->current_gold() >= q);
}

void Hero::remove_gold(unsigned int q) {
  inventory->remove_gold(q);
}


void Hero::unbank_item(unsigned int item_id) {
  if (ghost_mode)
    throw ModelException("Ghosts can't add items to inventory!", "5");
  meditating = false;
  if (inventory->is_full()) throw ModelException("Inventory is full!", "5");
  Item *i = bank->remove_item(item_id);
  if (!i) throw ModelException("Bank doesn't have that item!", "5");
  inventory->add_item(i);
}
void Hero::bank_item(unsigned int item_id) {
  if (ghost_mode)
    throw ModelException("Ghosts can't transfer items to bank!", "5");
  meditating = false;
  if (bank->is_full()) throw ModelException("Bank is full!", "5");
  Item *i = inventory->remove_item(item_id);
  if (!i) throw ModelException("Inventory doesn't have that item!", "5");
  bank->add_item(i);
}

Item *Hero::remove_item(unsigned int item_id) {
  if (ghost_mode)
    throw ModelException("Ghosts can't add items to inventory!", "5");
  meditating = false;
  Item *i = inventory->remove_item(item_id);
  return i;
}

void Hero::add_item(Item *item) {
  if (ghost_mode)
    throw ModelException("Ghosts can't add items to inventory!", "4");
  meditating = false;
  inventory->add_item(item);
}

bool Hero::has_free_space() { return (!inventory->is_full()); }

bool Hero::has_items_in_inventory() { return (!inventory->is_empty()); }

void Hero::add_gold(unsigned int gold) {
  inventory->add_gold(gold);
  // this->gold += gold;
}

void Hero::pick_up_drop(Drop *drop) {
  if (ghost_mode) throw ModelException("Ghosts can't pick up drops!", "4");
  if ((drop->size() > 0) && (this->has_free_space())) {
    // siempre tomo el ultimo item en el drop
    Item *item = drop->take_item(drop->size());
    this->add_item(item);
  } else if ((drop->ammount_of_gold() > 0) && this->can_hold_more_gold()) {
    unsigned int hero_gold_space = this->gold_space_remaining();
    unsigned int taken_gold = drop->take_gold(hero_gold_space);
    this->add_gold(taken_gold);
  }
}

bool Hero::can_hold_more_gold() {
  return (inventory->current_gold() < (max_safe_gold + max_safe_gold / 2));
}

unsigned int Hero::gold_space_remaining() {
  return ((max_safe_gold + max_safe_gold / 2) - inventory->current_gold());
}

bool Hero::has_excedent_coins() {
  return (inventory->current_gold() > max_safe_gold);
}

void Hero::notify_damage_done(BaseCharacter *other, unsigned int damage_done) {
  // std::cout << "My spell hit an enemy!!!" << std::endl;
  update_experience(damage_done, other);
  // std::cout << "Updated experience!!: " << experience << " out of "
  //           << next_level_xp_limit << std::endl;
  // std::cout << " My level is : " << level << std::endl;
}

const Attack Hero::attack() {
  if (ghost_mode) throw ModelException("Ghosts can't attack!", "3");
  // if (!close_enough(other)) throw ModelException("Too far to attack!", "7");
  if (!equipment->can_use_primary_weapon(this))
    throw ModelException("Cant use primary weapon! (not enough mana?)", "8");
  meditating = false;
  // mover a json!
  bool critical = false;
  unsigned int dmg = calculate_damage();
  float p = rand() / double(RAND_MAX);
  if (p < critical_damage_probability) critical = true;
  Attack attack = {dmg, critical, equipment->primary_weapon_id(),
                   equipment->range()};
  return std::move(attack);
}

unsigned int Hero::receive_damage(unsigned int damage, bool critical,
                                  unsigned int weapon_origin) {
  // std::cout << "Received damage!! " << damage << " is critical? " << critical
  //           << std::endl;
  if (ghost_mode) throw ModelException("Can't attack ghosts!", "2");
  meditating = false;
  // meter en json!
  // std::cout << "@@@Damage al ingresar receive damage: " << damage <<
  // std::endl;
  int actual_damage = damage;
  // std::cout << "@@@Damage al castear a int : " << actual_damage << std::endl;

  float p = pow(rand() / double(RAND_MAX), agility);
  if (critical) {
    actual_damage *= critical_damage_multiplier;
    // std::cout << "@@@Damage al multiplicar : " << actual_damage << std::endl;
  } else if (p < evasion_probability) {
    actual_damage = 0;
    // std::cout << "@@@Damage al evadir : " << actual_damage << std::endl;

  } else {
    actual_damage =
        std::max((int)damage - (int)equipment->get_defense_bonus(), 0);
    // std::cout << "@@@Damage al consultar max: " << actual_damage <<
    // std::endl;

  }  // Hacer chequeos si esta vivo etc?
  if (actual_damage > 0) {
    // std::cout << "changed hero affected by: " << affected_by << std::endl;
    affected_by = weapon_origin;
  }

  current_hp -= actual_damage;
  if (current_hp <= 0) ghost_mode = true;
  // std::cout << "Updated status!! HP: " << current_hp << "ghost? " <<
  // ghost_mode
  //           << std::endl;
  // std::cout << "@@@@@@@retornando " << actual_damage << std::endl;
  return actual_damage;
}

void Hero::meditate() {
  if (ghost_mode) throw ModelException("Can't meditate death!", "2");
  ;
  meditating = true;
}

bool Hero::is_death() { return ghost_mode; }

// void Hero::consume(unsigned int item_id) {
//   Item *consumable = inventory->remove_item(item_id);
//   consumable->use(this);
//   delete consumable;
// }

void Hero::revive() { ghost_mode = false; }

Hero::~Hero() {
  if (inventory) delete inventory;
  if (equipment) delete equipment;
  if (bank) delete bank;
}

/* private methods */

unsigned int Hero::calculate_damage() {
  return strength * equipment->get_attack_bonus();
}

void Hero::update_experience(unsigned int dmg_done, BaseCharacter *other) {
  experience += floor(
      dmg_done * std::max((other->level - this->level) + 10, (unsigned int)0));
  if (other->is_death()) {
    float p = rand() / double(RAND_MAX);
    experience +=
        floor(p * other->max_hp *
              std::max((other->level - this->level) + 10, (unsigned int)0));
  }
  while (experience >= next_level_xp_limit) {
    experience -= next_level_xp_limit;
    level_up();
  }
}

void Hero::level_up() {
  level++;
  max_hp = current_hp = constitution * f_class_hp * f_race_hp * level;
  max_mana = current_mana = intelligence * f_class_mana * f_race_mana * level;
  next_level_xp_limit =
      starting_xp_cap * floor(pow(level, level_up_limit_power));
  max_safe_gold = max_safe_gold_multiplier * level;
}

unsigned int Hero::remove_excess_gold() {
  unsigned int excess_gold = 0;

  if (inventory->current_gold() > max_safe_gold) {
    excess_gold = inventory->current_gold() - max_safe_gold;
    inventory->remove_gold(excess_gold);
    // gold = max_safe_gold;
  }
  return excess_gold;
}