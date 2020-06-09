#ifndef MAP_H
#define MAP_H
#include "tile.h"
#include "fixed_tile.h"
#include "base_character.h"
#include "stdint.h"
#include <vector>
#include <mutex>
class Map {
public:
	//b deberia ser un array con todos los que haya q posicionar
    Map(int cols, int rows);
    ~Map();
    void debug_print();
    /*
      Returns true if the character placed in x1,y1 could be
      moved to x2,y2. Else, it returns false and the character
      remains in it's last position. If moved, the character 
      position is also updated.
	*/
    bool move_character(int x1, int y1, int x2, int y2);
    void place_character(int x, int y, BaseCharacter* b);

private:
	int rows;
	int cols;
	std::vector<std::vector<Tile*> > matrix; 
  	std::mutex mutex;

};


#endif //MAP_H