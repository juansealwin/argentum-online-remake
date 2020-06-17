#include "map.h"

#include <iostream>

Map::Map(Json::Value &map_json)
    : rows(map_json["height"].asInt()), cols(map_json["width"].asInt()) {
  matrix.resize(rows);
  load_terrain(map_json);
}

void Map::load_terrain(Json::Value &map_json) {
  int curr_row = 0;
  int i = 0;  // para iterar sobre la data de json (lista)
  for (auto &it : matrix) {
    it.reserve(cols);
    for (int curr_col = 0; curr_col < cols; ++curr_col) {
      Tile *tile = nullptr;
      bool fixed = false;
      bool safe = false;
      int type = map_json["layers"][0]["data"][i].asInt();
      int type2 = map_json["layers"][1]["data"][i].asInt();
      char repr = '.';
      if (type2 != 0) {
        fixed = true;
        repr = 'b';
      } else if (type == FLOOR) {
        safe = true;
        repr = 'f';
      } else {
      }
      tile = new Tile(type, repr, safe, fixed);

      it.push_back(tile);
      i++;
    }
    curr_row++;
  }
}

Map::~Map() {
  for (auto &it : matrix) {
    for (auto p : it) {
      delete p;
    }
    it.clear();
  }
}

void Map::place_entity(int x, int y, Entity *e) {
  matrix[x][y]->place_entity(e);
}

bool Map::move_entity(int x1, int y1, int x2, int y2) {
  if (x2 >= rows || y2 >= cols || x2 < 0 || y2 < 0) return false;
  if (!matrix[x2][y2]->fixed) {
    //Cambiar este swap por poner al lugar como ocupado
    std::swap(matrix[x1][y1]->entity, matrix[x2][y2]->entity);
    return true;
  }
  return false;
}

void Map::debug_print() {
  for (auto &row : matrix) {
    for (auto &col : row) {
      std::cout << col->char_representation();
    }
    std::cout << std::endl;
  }
}
