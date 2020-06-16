#ifndef FIXED_TILE_H
#define FIXED_TILE_H
#include "tile.h"
class FixedTile : public Tile {
 public:
  FixedTile(int representation_id, char representation);
  virtual ~FixedTile();
  bool can_hold_character() override;
};

#endif  // FIXED_TILE_H
