#include "base_character.h"
#ifndef TILE_H
#define TILE_H
class Tile {
 public:
  explicit Tile(int representation_id, char representation, bool safe, bool fixed);
  ~Tile();
  Tile(const Tile &) = delete;
  char char_representation();
  void place_entity(Entity *character);
  Entity *entity = nullptr;

 private:
  int representation_id;
  char representation;
  bool safe;
  bool fixed;
  bool free;
  friend class Map;
};

#endif  // TILE_H
