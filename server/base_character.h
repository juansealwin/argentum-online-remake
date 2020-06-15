#include "entity.h"
#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter : public Entity {
 public:
  BaseCharacter(int x, int y, int type, char repr);
  virtual ~BaseCharacter();
  int x_position;
  int y_position;

 private:
  int type;
  char representation;
};

#endif  // BASE_CHARACTER_H
