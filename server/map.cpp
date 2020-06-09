#include "map.h"
#include <iostream>

std::vector<std::vector<char>> map_elements {
        { 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','w', 'w', 'w', 'w', 'w' , 'w', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','w', 'b', ',', ',', ',' , ',', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','w', 'p', ',', ',', ',' , ',', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','w', 'm', ',', ',', ',' , ',', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','w', 'w', 'w', '.', 'w' , 'w', 'w', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', '.', '.', '.', '.','.', '.', '.', '.', '.' , '.', '.', '.', '.', '.','.', '.', '.', '.', 'w' },
        { 'w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w','w', 'w', 'w', 'w', 'w' }
      };


Map::Map(int rows, int cols) : rows(rows), cols(cols) {
  matrix.resize(rows);
  int curr_row = 0;
  for (auto &it : matrix)
    {
      it.reserve(cols);
      for (int curr_col = 0; curr_col < cols; ++curr_col ) {
          Tile *tile = nullptr;
          char current_element = map_elements[curr_row][curr_col];
          if (current_element == '.') {
              tile = new Tile(current_element);
          } else {
              tile = new FixedTile(current_element);
          }
          it.push_back(tile);
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
        std::cout << col->char_representation() << " ";
     }
     std::cout << std::endl;
  }

}
