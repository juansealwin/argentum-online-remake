#include "entity.h"

Entity::Entity(int x, int y, int type, char repr)
    : x_position(x), y_position(y), type(type), representation(repr) {}

Entity::~Entity() {}

void Entity::set_x_y_position(int x, int y) {
  x_position = x;
  y_position = y;
}

int Entity::get_type() { return type; }

//bool Entity::is_movable() { return false; }

char Entity::char_representation() { return representation; }
