#ifndef MAP_H
#define MAP_H
#include "tile.h"
#include "fixed_tile.h"
#include "base_character.h"
#include "stdint.h"
#include <vector>
#include <mutex>
#include "../util/json/json.h"
//1st layer
#define GROUND 1
#define FLOOR 229
#define WALL_1 189
#define WALL_2 190
#define WALL_3 180
#define WALL_4 191
//2nd layer
#define PRIEST 498
#define MERCHANT 526
#define BANKER 495
#define GOBLIN 418
#define ZOMBIE 452
#define SPIDER 876
#define SKELETON 914
#define BUSH_1 164
#define BUSH_2 172

class Map {
public:
    //Map(int cols, int rows);
    //Crea un nuevo mapa a partir de un JSON
    Map(Json::Value &map_json);
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
  //Procesa la primera capa del mapa de tiled en el json
  void load_terrain(Json::Value &map_json);
	std::vector<std::vector<Tile*> > matrix; 
  	std::mutex mutex;
};


#endif //MAP_H