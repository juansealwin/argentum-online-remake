#include "map.h"
#include <iostream>

Map::Map(int rows, int cols, BaseCharacter* b) : rows(rows), cols(cols) {
  matrix.resize(rows);
  int y = 0;
  for (auto &it : matrix)
    {
      y++;
      it.reserve(cols);
      for (int x = 0; x < cols; ++x ) {
          Tile *tile = new Tile();
          if (y == 5 && x == 3) {
            //BaseCharacter *b = new BaseCharacter(x, y);
            tile->place_character(b);

          } 
          it.push_back(tile);
      }
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

void Map::move_character(int x1, int y1, int x2, int y2) {
  std::swap(matrix[x1][y1]->character, matrix[x2][y2]->character);
  matrix[x2][y2]->character->set_x_y_position(x2, y2);

}


void Map::debug_print() {

  for(auto& row:matrix){
     for(auto& col:row){
        std::cout << col->char_representation() << " ";
     }
     std::cout << std::endl;
  }

}
