#include "entity.h"
#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter : public Entity {
 public:
  BaseCharacter(int x, int y, int type, char repr, int max_hp, int level);
  BaseCharacter(int x, int y, int type, char repr, int level);
  BaseCharacter(int x, int y, int type, char repr);
  virtual ~BaseCharacter();
  BaseCharacter(const BaseCharacter &) = delete;

 protected:
  int max_hp;
  int level;
  int current_hp;
  int type;
  char representation;

};

#endif  // BASE_CHARACTER_H
