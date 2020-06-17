#include "base_character.h"
#include <iostream>
BaseCharacter::BaseCharacter(int x, int y, int type, char repr, int max_hp,
                             int level, Map *map)
    // : x_position(x), y_position(y), type(type), representation(repr) {}
    : Entity(x, y, type, repr),
      max_hp(max_hp),
      level(level),
      current_hp(max_hp),
      map(map) {}

BaseCharacter::BaseCharacter(int x, int y, int type, char repr,
                             int level, Map *map)
    // : x_position(x), y_position(y), type(type), representation(repr) {}
    : Entity(x, y, type, repr),
      level(level),
      map(map) {}

BaseCharacter::BaseCharacter(int x, int y, int type, char repr)
    // : x_position(x), y_position(y), type(type), representation(repr) {}
    : Entity(x, y, type, repr) {
  max_hp = current_hp = level = 1;
}

BaseCharacter::~BaseCharacter() {}
