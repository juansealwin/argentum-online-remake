#include "entity.h"
#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter : public Entity {
 public:
  BaseCharacter(int x, int y, int type, char repr, int hp, int level);
  BaseCharacter(int x, int y, int type, char repr);
  virtual ~BaseCharacter();

 private:
  int hp;
  int level;
  int type;
  char representation;

};

#endif  // BASE_CHARACTER_H
