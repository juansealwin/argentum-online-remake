#include "tile.h"

Tile::Tile(int representation_id, char representation, bool safe, bool fixed)
    : representation_id(representation_id),
      representation(representation),
      safe(safe),
      fixed(fixed),
      free(!fixed),
      entity_id(-1) {}

Tile::~Tile() {}

char Tile::char_representation() {
  if (free)
    return representation;
  else
    return 'o';
}

void Tile::empty_cell() { free = true; }

void Tile::fill_cell() { free = false; }