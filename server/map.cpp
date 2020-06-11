#include "map.h"
#include <iostream>

// std::vector<std::vector<char>> map_elements {
//         { 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','w', 'w', 'w', 'w', 'w' , 'w', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','w', 'b', ',', ',', ',' , ',', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','w', 'p', ',', ',', ',' , ',', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','w', 'm', ',', ',', ',' , ',', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','w', 'w', 'w', '.', 'w' , 'w', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
//         { 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w' }
//       };


//Map::Map(int rows, int cols) : rows(rows), cols(cols) {
Map::Map(Json::Value &map_json) : rows(map_json["height"].asInt()), cols(map_json["width"].asInt()) {
//  rows = ;
//  cols = ;
  matrix.resize(rows);
  load_terrain(map_json);
  debug_print();
}

void Map::load_terrain(Json::Value &map_json) {
  int curr_row = 0;
  int i = 0; //para iterar sobre la data de json (lista)
  for (auto &it : matrix)
      {
        it.reserve(cols);
        for (int curr_col = 0; curr_col < cols; ++curr_col ) {
          Tile *tile = nullptr;
          int type = map_json["layers"][0]["data"][i].asInt();
          if (type == GROUND) {
              int type2 = map_json["layers"][1]["data"][i].asInt();
              if (type2 == BUSH_1 || type2 == BUSH_2) {
                tile = new FixedTile(type, 'b');
              }
              else {
                tile = new FixedTile(type, '.');
              }
          } else if (type == FLOOR) {
            //Deberia ser un nuevo tipo, SafeTile donde los no monstruos puedan caminar
            //Usando metodos tipo canholdmonster y canholdcharacter
              tile = new FixedTile(type, ',');
          } else {

                tile = new FixedTile(type, 'w');
            
          }
          it.push_back(tile);
          i++;
        }
        curr_row++;
      }
}

Map::~Map() {
  for (auto &it : matrix)
    {
      for (auto p : it)
         {
           delete p;
         } 
         it.clear();
    }

}

void Map::place_character(int x, int y, BaseCharacter* b) {
  std::unique_lock<std::mutex> lock(mutex);
  matrix[x][y]->place_character(b);
}

bool Map::move_character(int x1, int y1, int x2, int y2) {
  std::unique_lock<std::mutex> lock(mutex);
  if (matrix[x2][y2]->can_hold_character()) {
    std::swap(matrix[x1][y1]->character, matrix[x2][y2]->character);
    matrix[x2][y2]->character->set_x_y_position(x2, y2);
    return true;
  }
  return false;
}


void Map::debug_print() {
  std::unique_lock<std::mutex> lock(mutex);
  for(auto& row:matrix){
     for(auto& col:row){
        std::cout << col->char_representation();
     }
     std::cout << std::endl;
     }
}
