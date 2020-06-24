#ifndef MAP_H
#define MAP_H
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "stdint.h"
#include "tile.h"
// 1st layer
#define GROUND 1
#define FLOOR 1217
// 2nd layer
#define TREE_1 1153
#define TREE_2 1216
#define HOUSE_1 1025
#define HOUSE_2 1064
#define HOUSE2_1 1089
#define HOUSE2_2 1112

class Map {
 public:
  // Map(int cols, int rows);
  // Crea un nuevo mapa a partir de un JSON
  Map(Json::Value &map_json);
  ~Map();
  void debug_print();

  void empty_cell(int x, int y);
  bool can_ocupy_cell(int x, int y);
  /*
  Devuelve true si el personaje colocado en x1,y1
  puede moverse a x2,y2. Si no, devuelve false. Es responsabilidad luego
  actualizar el x,y de la entidad. La celda en x1,y1 quedara como liberada,
  x2,y2 ocupada. Se debe llamar a empty_cell con el lugar anterior.
    */
  bool ocupy_cell(int x, int y);
  Map(const Map &) = delete;
  bool tile_is_safe(int x, int y);
  std::tuple<int, int> get_random_free_space();
 private:
  int rows;
  int cols;
  // Procesa la primera capa del mapa de tiled en el json
  void load_terrain(Json::Value &map_json);
  std::vector<std::vector<Tile *> > matrix;
  
};

#endif  // MAP_H