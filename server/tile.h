#include "base_character.h"
#ifndef TILE_H
#define TILE_H
class Tile {
public:
    explicit Tile();
    ~Tile();
    char char_representation();
    void place_character(BaseCharacter *character);
    BaseCharacter *character = nullptr;

private:
    char representation = 'f';
};

#endif //TILE_H