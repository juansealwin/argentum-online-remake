
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "entity.h"
#include "map.h"
#include "stdint.h"

struct Attack {
  unsigned int damage;
  bool critical;
  unsigned int attacker_weapon_id;
  unsigned int attacker_weapon_range;
};

class Map;
class BaseCharacter : public Entity {
 public:
  // Este primer constructor lo usa la clase hija Monster
  BaseCharacter(unsigned int unique_id, int x, int y, unsigned int type,
                char repr, unsigned int max_hp, unsigned int level, Map *map,
                const std::string &name);
  virtual ~BaseCharacter();
  BaseCharacter(const BaseCharacter &) = delete;
  virtual unsigned int receive_damage(unsigned int damage, bool critical,
                                      unsigned int weapon_origin) = 0;
  //devuelve true si se movio a la sig posicion, false si no
  //muevase o no el pj, cambia su orientacion
  virtual bool move(int next_x, int next_y);
  virtual bool is_death() = 0;
  virtual const Attack attack() = 0;
  virtual void notify_damage_done(BaseCharacter *other,
                                  unsigned int damage_done) = 0;
  void set_position(int x, int y);
  void set_map(Map *map);
  virtual std::string get_name();
  // remueve efecto que recibe por las armas
  void clear_effects();
  int current_hp;
  unsigned int max_hp;
  unsigned int level;
  unsigned int affected_by;

 protected:
  Map *map;
  std::string name;

 private:
  // settea orientacion segun el movimiento del personaje:
  void change_orientation(int old_x, int old_y, int new_x, int new_y);
};

#endif  // BASE_CHARACTER_H
