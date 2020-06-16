#include "map.h"

#include <iostream>

Map::Map(Json::Value &map_json)
    : rows(map_json["height"].asInt()), cols(map_json["width"].asInt()) {
  matrix.resize(rows);
  load_terrain(map_json);
}

// void Map::load_terrain(Json::Value &map_json) {
//   int curr_row = 0;
//   int i = 0;  // para iterar sobre la data de json (lista)
//   for (auto &it : matrix) {
//     it.reserve(cols);
//     for (int curr_col = 0; curr_col < cols; ++curr_col) {
//       Tile *tile = nullptr;
//       int type = map_json["layers"][0]["data"][i].asInt();
//       if (type == GROUND) {
//         int type2 = map_json["layers"][1]["data"][i].asInt();
//         if (type2 >= TREE_1 && type2 <= TREE_2) {
//           tile = new FixedTile(type, 't');
//         } else if (type2 >= HOUSE_1 && type2 <= HOUSE_2) {
//           tile = new FixedTile(type, 'h');
//         } else if (type2 >= HOUSE2_1 && type2 <= HOUSE2_2) {
//           tile = new FixedTile(type, 'h');
//         } else if (type2 != 0) {
//           std::cout << "Missing type: " << type2 << std::endl;
//         } else {
//           tile = new Tile(type, '.');
//         }
//       } else if (type == FLOOR) {
//         // Deberia ser un nuevo tipo, SafeTile donde los no monstruos puedan
//         // caminar Usando metodos tipo canholdmonster y canholdcharacter
//         int type2 = map_json["layers"][1]["data"][i].asInt();
//         if ((type2 >= HOUSE_1 && type2 <= HOUSE_2) ||
//             (type2 >= HOUSE2_1 && type2 <= HOUSE2_2)) {
//           tile = new FixedTile(type, 'h');
//         }
//         else {
//           tile = new FixedTile(type, ',');
//         }
//       } else {
//         tile = new FixedTile(type, 'w');
//       }
//       if (tile) it.push_back(tile);
//       i++;
//     }
//     curr_row++;
//   }
// }

void Map::load_terrain(Json::Value &map_json) {
  int curr_row = 0;
  int i = 0;  // para iterar sobre la data de json (lista)
  for (auto &it : matrix) {
    it.reserve(cols);
    for (int curr_col = 0; curr_col < cols; ++curr_col) {
      Tile *tile = nullptr;
      int type = map_json["layers"][0]["data"][i].asInt();
      int type2 = map_json["layers"][1]["data"][i].asInt();
      if (type2 != 0) {
        tile = new FixedTile(type, 'b');
      } else if (type == FLOOR) {
        tile = new Tile(type, ',');
      } else {
        tile = new Tile(type, '.');
      }
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

void Map::place_character(int x, int y, BaseCharacter *b) {
  matrix[x][y]->place_character(b);
}

bool Map::move_entity(int x1, int y1, int x2, int y2) {
  if (x2 >= rows || y2 >= cols || x2 < 0 || y2 < 0) return false;
  if (matrix[x2][y2]->can_hold_character()) {
    std::swap(matrix[x1][y1]->character, matrix[x2][y2]->character);
    matrix[x2][y2]->character->set_x_y_position(x2, y2);
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
