#include "stdint.h"
#include "entity.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter : public Entity{
 public:
  BaseCharacter(int x, int y, int type, char repr);
  virtual ~BaseCharacter();
  //char char_representation();
  //virtual bool is_movable();
  //void set_x_y_position(int x, int y);
  //int get_type();
  int x_position;
  int y_position;

 private:
  int type;
  char representation;
};

#endif  // BASE_CHARACTER_H
