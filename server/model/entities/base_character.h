
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "entity.h"
#include "map.h"
#include "stdint.h"

class Map;
class BaseCharacter : public Entity {
 public:
  // Este primer constructor lo usa la clase hija Monster
  BaseCharacter(unsigned int unique_id, int x, int y, unsigned int type,
                char repr, unsigned int max_hp, unsigned int level, Map *map);
  // Este segundo constructor lo usa el heroe ya que max_hp en ese caso es
  // calculado
  BaseCharacter(unsigned int unique_id, int x, int y, unsigned int type,
                char repr, unsigned int level, Map *map);
  virtual ~BaseCharacter();
  BaseCharacter(const BaseCharacter &) = delete;
  virtual unsigned int receive_damage(unsigned int damage, bool critical,
                                      unsigned int weapon_origin) = 0;
  virtual void move(int next_x, int next_y);
  virtual bool is_death() = 0;
  virtual void notify_damage_done(BaseCharacter *other,
                                  unsigned int damage_done) = 0;
  //remueve efecto que recibe por las armas
  void clear_effects();
  int current_hp;
  unsigned int max_hp;
  unsigned int level;
  unsigned int affected_by;

 protected:
  char representation;
  Map *map;

 private:
  // settea orientacion segun el movimiento del personaje:
  // 0: mirando hacia arriba
  // 1: hacia la derecha
  // 2: hacia abajo
  // 3: hacia la izquierda
  void change_orientation(int old_x, int old_y, int new_x, int new_y);
};

#endif  // BASE_CHARACTER_H
