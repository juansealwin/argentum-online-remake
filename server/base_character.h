#include "entity.h"
#include "stdint.h"
#include "map.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
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

  int current_hp;
  int max_hp;

 protected:
  int level;
  int type;
  char representation;
  Map *map;
};

#endif  // BASE_CHARACTER_H
