#include "base_character.h"

BaseCharacter::BaseCharacter(int x, int y, int type, char repr)
    : x_position(x), y_position(y), type(type), representation(repr) {}

BaseCharacter::~BaseCharacter() {}

void BaseCharacter::set_x_y_position(int x, int y) {
  x_position = x;
  y_position = y;
}

int BaseCharacter::get_type() { return type; }

bool BaseCharacter::is_movable() { return false; }

char BaseCharacter::char_representation() { return representation; }
