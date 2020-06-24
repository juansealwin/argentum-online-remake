
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "entity.h"
#include "map.h"
#include "stdint.h"
class Map;
class BaseCharacter : public Entity {
 public:
  // Este primer constructor lo usa la clase hija Monster
  BaseCharacter(int x, int y, unsigned int type, char repr, unsigned int max_hp,
                unsigned int level, Map *map);
  // Este segundo constructor lo usa el heroe ya que max_hp en ese caso es
  // calculado
  BaseCharacter(int x, int y, unsigned int type, char repr, unsigned int level,
                Map *map);
  virtual ~BaseCharacter();
  BaseCharacter(const BaseCharacter &) = delete;
  virtual unsigned int damage(BaseCharacter *other) = 0;
  virtual unsigned int receive_damage(unsigned int damage, bool critical) = 0;
  virtual void move(int next_x, int next_y);
  unsigned int current_hp;
  unsigned int max_hp;

 protected:
  unsigned int level;
  unsigned int type;
  char representation;
  Map *map;
};

#endif  // BASE_CHARACTER_H
