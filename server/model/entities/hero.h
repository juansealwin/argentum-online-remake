
#ifndef HERO_H
#define HERO_H

#include <cmath>

#include "base_character.h"
#include "equipment.h"
#include "inventory.h"
#include "monster.h"
#include "stdint.h"

// meter en el json!
class Inventory;
class Item;
class Drop;
class Hero : public BaseCharacter {
 public:
  // constructor para heroes nuevos
  Hero(unsigned int unique_id, int x, int y, unsigned int race_id, char repr,
       unsigned int level, unsigned int strength, unsigned int intelligence,
       unsigned int agility, unsigned int constitution, unsigned int f_class_hp,
       unsigned int f_race_hp, unsigned int f_race_recovery,
       unsigned int f_race_mana, unsigned int f_class_mana,
       unsigned int f_class_meditation, unsigned int gold,
       unsigned int class_id, Map *map, std::string name,
       const float critical_damage_multiplier,
       const unsigned int inventory_size,
       const float critical_damage_probability, const float evasion_probability,
       const float max_safe_gold_multiplier, const float level_up_limit_power,
       const float starting_xp_cap, const unsigned int bank_size);
  // Hero(Hero* h, Map &map);
  void regenerate();
  // curacion en cada update
  void heal(unsigned int hp, unsigned int mana);
  // movimiento segun la velocidad en cada update
  void auto_move();
  // devuelve el dano causado
  void set_speed_x(int x);
  void set_speed_y(int y);
  const Attack attack();
  // devuelve el dano que efectivamente recibi
  virtual unsigned int receive_damage(unsigned int damage, bool critical,
                                      unsigned int weapon_origin) override;
  // recibe al jugador que hizo dano su ataque y el dano hecho
  virtual void notify_damage_done(BaseCharacter *other,
                                  unsigned int damage_done) override;
  // PRE: Se llama a unequip_x antes de equip_x para que lo guarde en
  // inventario.

  void equip_weapon(unsigned int weapon_id);
  void equip_staff(unsigned int staff_id);
  void equip_shield(unsigned int shield_id);
  void equip_helmet(unsigned int helmet_id);
  void equip_armour(unsigned int armour_id);
  void use_item(unsigned int item_id);
  void use_special_staff();
  void unequip(unsigned int item_id);
  void unequip_weapon();
  void unequip_staff();
  void unequip_shield();
  void unequip_helmet();
  void unequip_armour();

  // quita item del banco y lo guarda en el inventario
  void unbank_item(unsigned int item_id);
  // transfiere item del inventario al banco
  void bank_item(unsigned int item_id);
  void unbank_gold(unsigned int ammount);
  void bank_gold(unsigned int ammount);

  // devuelve el Item en el inventario con el id buscado. Devuelve nullptr si no
  // lo tiene
  Item *remove_item(unsigned int item_id);
  // Agrega un item al inventario, lanza excepcion si este esta lleno
  void add_item(Item *item);
  void add_gold(unsigned int gold);
  // Empieza a meditar. Se termina de meditar una vez que se hace cualquier otra
  // cosa (llamado a cualquier otro metodo)
  bool has_free_space();
  bool has_items_in_inventory();
  // devuelve true
  bool can_hold_more_gold();
  bool has_excedent_coins();
  void pick_up_drop(Drop *drop);
  // devuelve cuantas mas monedas puede guardar el heroe
  unsigned int gold_space_remaining();
  bool has_gold(unsigned int q);
  void meditate();
  virtual ~Hero();
  Hero(const Hero &) = delete;
  virtual bool is_death() override;
  // consume un item (Deberia ser llamado solo para pociones)
  // para el caso del staff que cura podria hacerse algo parecido
  void consume(unsigned int item_id);
  void revive();
  unsigned int remove_excess_gold();
  void remove_gold(unsigned int q);
  void set_close_to_npc(bool val);
  void try_to_unblock();
  // bloquea a un heroe durante x segundos, una vez que paso el tiempo, es
  // revivido en la posicion x, y
  void block(unsigned int seconds, int x, int y);
  friend class Staff;
  friend class Weapon;
  friend class DefensiveItem;
  friend class Serializer;
  friend class DropsManager;
  friend class ArgentumGame;
  unsigned int current_mana;
  unsigned int max_mana;

 private:
  // inicializados en member initialization list
  unsigned int strength, intelligence, agility, constitution, f_class_hp,
      f_race_hp, f_race_recovery, f_race_mana, f_class_mana, f_class_meditation,
      class_id, experience,  respawn_x, respawn_y;
  int speed_x, speed_y;
  bool meditating, ghost_mode, close_to_npc, blocked;

  std::string name;
  // config
  float critical_damage_multiplier, critical_damage_probability,
      evasion_probability, max_safe_gold_multiplier, level_up_limit_power,
      starting_xp_cap;

  // calculados
  unsigned int next_level_xp_limit, max_safe_gold;
  Equipment *equipment;
  Inventory *inventory;
  Inventory *bank;
  std::chrono::time_point<std::chrono::high_resolution_clock>
      wait_starting_time;
  unsigned blocked_seconds_duration;

  // metodos privados
  unsigned int calculate_damage();
  // actualiza la experiencia, sube niveles
  void update_experience(unsigned int dmg_done, BaseCharacter *other);
  void level_up();
  void set_hp(unsigned int hp);
  void set_mana(unsigned int mana);
};
#endif  // HERO_H
