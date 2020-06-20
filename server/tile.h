#include "base_character.h"
#ifndef TILE_H
#define TILE_H
class Tile {
 public:
  explicit Tile(int representation_id, char representation, bool safe, bool fixed);
  ~Tile();
  Tile(const Tile &) = delete;
  char char_representation();
  void fill_cell();
  void empty_cell();

 private:
  int representation_id;
  char representation;
  bool safe;
  bool fixed;
  bool free;
  friend class Map;
};

#endif  // TILE_H
