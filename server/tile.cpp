#include "tile.h"

Tile::Tile(int representation_id, char representation, bool safe, bool fixed)
    : representation_id(representation_id), representation(representation), safe(safe), fixed(fixed), free(fixed) {}

Tile::~Tile() {}

char Tile::char_representation() {
  if (entity) {
    return entity->char_representation();
  }
  return representation;
}

void Tile::place_entity(Entity *e) { entity = e; }

//bool Tile::can_hold_character() { return entity == nullptr; }

//void Tile::place_character(BaseCharacter *b) { character = b; }
