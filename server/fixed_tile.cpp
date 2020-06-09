#include "fixed_tile.h"

FixedTile::FixedTile(char representation) : Tile(representation) {}

bool FixedTile::can_hold_character() {
	return false;
}
