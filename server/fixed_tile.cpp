#include "fixed_tile.h"

FixedTile::FixedTile(int representation_id, char representation)
 : Tile(representation_id, representation) {}

bool FixedTile::can_hold_character() {
	return false;
}
