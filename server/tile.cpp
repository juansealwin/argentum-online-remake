#include "tile.h"

Tile::Tile(char representation) : representation(representation) {}

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

bool Tile::can_hold_character() {
	return character == nullptr;
}

void Tile::place_character(BaseCharacter *b) {
	character = b;
}
