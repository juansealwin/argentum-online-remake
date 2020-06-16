#include "base_character.h"

BaseCharacter::BaseCharacter(int x, int y, int type, char repr, int hp,
                             int level)
    // : x_position(x), y_position(y), type(type), representation(repr) {}
    : Entity(x, y, type, repr), hp(hp), level(level) {}

BaseCharacter::BaseCharacter(int x, int y, int type, char repr)
    // : x_position(x), y_position(y), type(type), representation(repr) {}
    : Entity(x, y, type, repr) {
  hp = level = 1;
}

BaseCharacter::~BaseCharacter() {}
