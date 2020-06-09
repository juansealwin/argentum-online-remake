#include "tile.h"

Tile::Tile() {}

Tile::~Tile() {
	if (character) {
		delete character;
	}
}

char Tile::char_representation() {
	if (character) {
		return character->char_representation();
	}
	return representation;
}

void Tile::place_character(BaseCharacter *b) {
	character = b;
}
