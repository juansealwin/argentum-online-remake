#include "tile.h"

Tile::Tile(int representation_id, char representation)
    : representation_id(representation_id), representation(representation) {}

Tile::~Tile() {}

char Tile::char_representation() {
  if (character) {
    return character->char_representation();
  }
  return representation;
}

bool Tile::can_hold_character() { return character == nullptr; }

void Tile::place_character(BaseCharacter *b) { character = b; }
