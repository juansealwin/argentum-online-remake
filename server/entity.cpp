#include "entity.h"

Entity::Entity(int x, int y, int type, char repr)
    : x_position(x), y_position(y), type(type), representation(repr) {}

Entity::~Entity() {}

int Entity::get_type() { return type; }

char Entity::char_representation() { return representation; }
