#include "tile.h"

Tile::Tile(int representation_id, char representation, bool safe, bool fixed)
    : entity_id(-1),
      representation_id(representation_id),
      representation(representation),
      safe(safe),
      fixed(fixed),
      free(!fixed) {}

Tile::~Tile() {}

char Tile::char_representation() {
  if (free)
    return representation;
  else
    return 'o';
}

void Tile::empty_cell() {
  entity_id = -1;
  free = true;
}

void Tile::fill_cell(unsigned int uid) {
  entity_id = uid;
  free = false;
}