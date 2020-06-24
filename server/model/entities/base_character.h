
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "entity.h"
#include "stdint.h"
#include "map.h"
class Map;
class BaseCharacter : public Entity {
 public:
  // Este primer constructor lo usa la clase hija Monster
  BaseCharacter(int x, int y, int type, char repr, int max_hp, int level, Map* map);
  // Este segundo constructor lo usa el heroe ya que max_hp en ese caso es
  // calculado
  BaseCharacter(int x, int y, int type, char repr, int level, Map* map);
  virtual ~BaseCharacter();
  BaseCharacter(const BaseCharacter &) = delete;
  virtual unsigned int damage(BaseCharacter *other) = 0;
  virtual unsigned int receive_damage(unsigned int damage, bool critical) = 0;
  int current_hp;
  int max_hp;
  bool alive = true;

 protected:
  int level;
  int type;
  char representation;
  Map *map;
};

#endif  // BASE_CHARACTER_H
