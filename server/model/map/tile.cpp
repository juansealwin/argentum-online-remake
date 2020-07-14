#include "tile.h"

Tile::Tile(int representation_id, char representation, bool safe, bool fixed)
    : entity_id(-1),
      representation_id(representation_id),
      representation(representation),
      safe(safe),
      fixed(fixed),
      free(!fixed),
      has_projectile(false) {}

Tile::~Tile() {}

char Tile::char_representation() {
  if (free)
    return representation;
  else
    return 'o';
}

void Tile::fill_with_projectile() {
  has_projectile = true;
}

void Tile::clean_projectile() {
  has_projectile = false;
}

void Tile::empty_cell() {
  entity_id = -1;
  free = true;
  has_projectile = false;
}

void Tile::fill_cell(unsigned int uid) {
  entity_id = uid;
  free = false;
}