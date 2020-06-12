#include "base_character.h"

BaseCharacter::BaseCharacter(int x, int y, int id, char repr) :
		x_position(x), y_position(y), id(id), representation(repr) {
}

BaseCharacter::~BaseCharacter() {}

void BaseCharacter::set_x_y_position(int x, int y) {
	x_position = x;
	y_position = y;
}

bool BaseCharacter::is_movable() {
	return false;
}

char BaseCharacter::char_representation() {
	return representation;
}
