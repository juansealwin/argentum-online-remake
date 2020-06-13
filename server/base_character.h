#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter {
 public:
  BaseCharacter(int x, int y, int id, char repr);
  ~BaseCharacter();
  char char_representation();
  virtual bool is_movable();
  void set_x_y_position(int x, int y);
  int x_position;
  int y_position;

 private:
  int id;
  char representation;
};

#endif  // BASE_CHARACTER_H
