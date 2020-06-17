#ifndef MAP_H
#define MAP_H
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "base_character.h"
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
  /*
    Devuelve true si el personaje colocado en x1,y1
    puede moverse a x2,y2. Si no, devuelve false. Es responsabilidad luego
    actualizar el x,y de la entidad
      */
  bool move_entity(int x1, int y1, int x2, int y2);
  // Posiciona un personaje en la fila x, columna y
  // void place_character(int x, int y, BaseCharacter *b);
  void place_entity(int x, int y, Entity *e);
  Map(const Map &) = delete;

 private:
  int rows;
  int cols;
  // Procesa la primera capa del mapa de tiled en el json
  void load_terrain(Json::Value &map_json);
  std::vector<std::vector<Tile *> > matrix;
};

#endif  // MAP_H