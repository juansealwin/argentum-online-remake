#include "base_character.h"
#ifndef TILE_H
#define TILE_H
class Tile {
 public:
  explicit Tile(int representation_id, char representation);
  ~Tile();
  char char_representation();
  void place_character(BaseCharacter *character);
  virtual bool can_hold_character();
  BaseCharacter *character = nullptr;

 private:
  int representation_id;
  char representation;
};

#endif  // TILE_H
