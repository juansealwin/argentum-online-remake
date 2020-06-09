#include "base_character.h"

BaseCharacter::BaseCharacter(int x, int y) :
							x_position(x), y_position(y) {
}

BaseCharacter::~BaseCharacter() {}

void BaseCharacter::set_x_y_position(int x, int y) {
	x_position = x;
	y_position = y;
}

char BaseCharacter::char_representation() {
	return representation;
}
