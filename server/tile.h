#include "base_character.h"
#ifndef TILE_H
#define TILE_H
class Tile {
 public:
  explicit Tile(int representation_id, char representation);
  virtual ~Tile();
  Tile(const Tile &) = delete;
  char char_representation();
  //void place_character(BaseCharacter *character);
  void place_entity(Entity *character);
  virtual bool can_hold_character();
  //BaseCharacter *character = nullptr;
  Entity *entity = nullptr;

 private:
  int representation_id;
  char representation;
};

#endif  // TILE_H
