
#ifndef HERO_H
#define HERO_H

#include <cmath>

#include "base_character.h"
#include "equipment.h"
#include "inventory.h"
#include "monster.h"
#include "stdint.h"
// meter en el json!
#define CRITICAL_DAMAGE_MULTIPLIER 2
#define INVENTORY_SIZE 20
class Inventory;
class Item;
class Hero : public BaseCharacter {
 public:
  // constructor para heroes nuevos
  Hero(int x, int y, unsigned int race_id, char repr, unsigned int level,
       unsigned int strength, unsigned int intelligence, unsigned int agility,
       unsigned int constitution, unsigned int f_class_hp,
       unsigned int f_race_hp, unsigned int f_race_recovery,
       unsigned int f_race_mana, unsigned int f_class_mana,
       unsigned int f_class_meditation, unsigned int gold,
       unsigned int class_id, Map *map);
  // devuelve el dano causado
  void update() override;
  virtual unsigned int damage(BaseCharacter *other) override;
  // unsigned int damage(Hero *other);
  // unsigned int damage(Monster *m);
  // devuelve el dano que efectivamente recibi
  virtual unsigned int receive_damage(unsigned int damage,
                                      bool critical) override;
  // PRE: Se llama a unequip_x antes de equip_x para que lo guarde en
  // inventario.
  void equip_weapon(unsigned int weapon_id);
  void equip_staff(unsigned int staff_id);
  void equip_shield(unsigned int shield_id);
  void equip_helmet(unsigned int helmet_id);
  void equip_armour(unsigned int armour_id);
  void unequip_weapon();
  void unequip_staff();
  void unequip_shield();
  void unequip_helmet();
  void unequip_armour();
  // devuelve el Item en el inventario con el id buscado. Devuelve nullptr si no
  // lo tiene
  Item *remove_item(unsigned int item_id);
  // Agrega un item al inventario, lanza excepcion si este esta lleno
  void add_item(Item *item);
  // Empieza a meditar. Se termina de meditar una vez que se hace cualquier otra
  // cosa (llamado a cualquier otro metodo)
  void meditate();
  virtual ~Hero();
  Hero(const Hero &) = delete;
  virtual bool is_death() override;
  friend class Staff;
  unsigned int current_mana;
  unsigned int max_mana;

 private:
  // inicializados en member initialization list
  unsigned int strength;
  unsigned int intelligence;
  unsigned int agility;
  unsigned int constitution;
  unsigned int f_class_hp;
  unsigned int f_race_hp;
  unsigned int f_race_recovery;
  unsigned int f_race_mana;
  unsigned int f_class_mana;
  unsigned int f_class_meditation;
  unsigned int gold;
  unsigned int class_id;
  unsigned int experience;
  bool meditating;
  bool ghost_mode;
  // calculados
  unsigned int next_level_xp_limit;
  unsigned int max_safe_gold;
  Equipment *equipment;
  Inventory *inventory;

  // metodos privados
  unsigned int calculate_damage();
  bool close_enough(BaseCharacter *other);
  // actualiza la experiencia, sube niveles
  void update_experience(unsigned int dmg_done, BaseCharacter *other);
  void level_up();
};
#endif  // HERO_H
