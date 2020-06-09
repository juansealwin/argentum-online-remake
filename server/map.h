#include "tile.h"
#include "base_character.h"
#include "stdint.h"
#include <vector>
#ifndef MAP_H
#define MAP_H

class Map {
public:
    Map(int cols, int rows);
    ~Map();
    void debug_print();
    /*
      This function should only be called when swapping 
	  a tile that has a BaseCharacter to another
	  x1,y1 is origin x2,y2 is destination.

	  If not, this should raise no error since it will swap
	  two nullptr.
	*/
    void move_character(int x1, int y1, int x2, int y2);

private:
	std::vector<std::vector<Tile*> > matrix; 
	int rows;
	int cols;
};


#endif //MAP_H