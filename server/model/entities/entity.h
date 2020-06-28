#ifndef ENTITY_H
#define ENTITY_H
#include "model_exceptions.h"
class Entity {
 public:
  Entity(int x, int y, int type, char repr);
  Entity(const Entity &) = delete;
  virtual ~Entity();
  virtual char char_representation();
  virtual void update() = 0;
  int x_position;
  int y_position;
  int type;
  bool alive;
  //toma valores de 0 a 3
  uint8_t orientation;

 private:

  char representation;
};

#endif  // ENTITY_H
