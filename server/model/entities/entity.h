#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
  orientation_down,
  orientation_right,
  orientation_left,
  orientation_up
} orientation_t;

#include "model_exceptions.h"
class Entity {
 public:
  Entity(unsigned int unique_id, int x, int y, int type, char repr,
         orientation_t orientation);
  Entity(const Entity &) = delete;
  virtual ~Entity();
  virtual char char_representation();
  unsigned int unique_id;
  int x_position;
  int y_position;
  int type;
  bool alive;
  // toma valores de 0 a 3
  orientation_t orientation;

 private:
  char representation;
};

#endif  // ENTITY_H
