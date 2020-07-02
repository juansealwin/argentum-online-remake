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
        if ((type2 >= TREE_1) && (type2 <= TREE_2)) {
          if (type2 == TREE_ROOT) {
            fixed = true;
            repr = 'b';
          } else {
            fixed = false;
          }
        } else {
          fixed = true;
          repr = 'b';
        }
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

std::tuple<int, int> Map::get_random_free_space() {
  while (true) {
    int x = rand() % 100;
    int y = rand() % 100;
    if (matrix[x][y]->free && !matrix[x][y]->fixed) {
      return std::tuple<int, int>(x, y);
    }
  }
}

bool Map::tile_is_valid(int x, int y) { 
  if (x >= rows || y >= cols || x < 0 || y < 0) return false;
  return true;
}

void Map::empty_cell(int x, int y) {
  if (x >= rows || y >= cols || x < 0 || y < 0) return;
  matrix[x][y]->empty_cell();
}

bool Map::tile_is_safe(int x, int y) {
  if (x >= rows || y >= cols || x < 0 || y < 0) return false;
  return matrix[x][y]->safe;
}

bool Map::can_ocupy_cell(int x, int y) {
  if (x >= rows || y >= cols || x < 0 || y < 0) return false;
  if (matrix[x][y]->fixed || !matrix[x][y]->free) return false;
  return true;
}

bool Map::ocupy_cell(int x, int y, unsigned int entity_id) {
  if (!can_ocupy_cell(x, y)) return false;
  matrix[x][y]->fill_cell(entity_id);
  return true;
}

void Map::debug_print() {
  for (auto &row : matrix) {
    for (auto &col : row) {
      std::cout << col->char_representation();
    }
    std::cout << std::endl;
  }
}

int Map::get_uid(int x, int y) {
  
  return matrix[x][y]->entity_id;
}
