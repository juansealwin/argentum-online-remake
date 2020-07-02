#include "entity.h"

Entity::Entity(unsigned int unique_id, int x, int y, int type, char repr)
    : unique_id(unique_id),
      x_position(x),
      y_position(y),
      type(type),
      representation(repr),
      alive(true),
      orientation(orientation_down) {}

Entity::~Entity() {}

char Entity::char_representation() { return representation; }
