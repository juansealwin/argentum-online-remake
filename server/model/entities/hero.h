
#ifndef HERO_H
#define HERO_H
#include "base_character.h"
#include "equipment.h"
#include "stdint.h"

#define CRITICAL_DAMAGE_MULTIPLIER 2
class Hero : public BaseCharacter {
 public:
  Hero(int x, int y, int race_id, char repr, int level, int strength,
       int intelligence, int agility, int constitution, int f_class_hp,
       int f_race_hp, int f_race_recovery, int f_race_mana, int f_class_mana,
       int f_class_meditation, int gold, int class_id, Map *map);
  // devuelve el dano causado
  void update() override;
  int damage(Hero *other);
  // devuelve el dano que efectivamente recibi
  int receive_damage(int damage, bool critical);
  // PRE: Se llama a unequip_x antes de equip_x para que lo guarde en
  // inventario. refactorizar para que los metodos de equip reciban un id y los
  // busquen en su inventario
  void equip_weapon(Weapon *weapon);
  void equip_staff(Staff *staff);
  void equip_shield(DefensiveItem *shield);
  void equip_helmet(DefensiveItem *helmet);
  void equip_armour(DefensiveItem *armour);
  void unequip_weapon();
  void unequip_staff();
  void unequip_shield();
  void unequip_helmet();
  void unequip_armour();
  virtual ~Hero();
  Hero(const Hero &) = delete;
  friend class Staff;
  int current_mana;
  int max_mana;

 private:
  int strength;
  int intelligence;
  int agility;
  int constitution;
  int f_class_hp;
  int f_race_hp;
  int f_race_recovery;
  int f_race_mana;
  int f_class_mana;
  int f_class_meditation;
  int gold;
  int class_id;
  Equipment *equipment;
};
#endif  // HERO_H
