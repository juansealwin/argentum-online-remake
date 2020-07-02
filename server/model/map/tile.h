#include "base_character.h"
#ifndef TILE_H
#define TILE_H
class Tile {
 public:
  explicit Tile(int representation_id, char representation, bool safe, bool fixed);
  ~Tile();
  Tile(const Tile &) = delete;
  char char_representation();
  void fill_cell(unsigned int uid);
  void empty_cell();
  int entity_id;

 private:
  int representation_id;
  char representation;
  bool safe;
  bool fixed;
  bool free;
  //id de la entidad que esta ocupando la celda (o -1 si no tiene)
  friend class Map;
};

#endif  // TILE_H
