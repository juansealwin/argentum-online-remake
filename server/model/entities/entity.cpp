#include "entity.h"

Entity::Entity(int x, int y, int type, char repr)
    : x_position(x),
      y_position(y),
      type(type),
      representation(repr),
      alive(true),
      orientation(0) {}

Entity::~Entity() {}

char Entity::char_representation() { return representation; }
