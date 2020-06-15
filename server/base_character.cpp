#include "base_character.h"

BaseCharacter::BaseCharacter(int x, int y, int type, char repr)
    // : x_position(x), y_position(y), type(type), representation(repr) {}
    : Entity(x, y, type, repr) {}

BaseCharacter::~BaseCharacter() {}
