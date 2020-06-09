#ifndef FIXED_TILE_H
#define FIXED_TILE_H
#include "tile.h"
class FixedTile : public Tile {
public:
    explicit FixedTile(char representation);
    ~FixedTile();
    bool can_hold_character() override;

};

#endif //FIXED_TILE_H