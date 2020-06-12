#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H
#include "../util/thread.h"
#include "map.h"
#include <vector>
#include <unistd.h>
#include "../util/json/json.h"
#include <fstream>
#include "base_character.h"
#include "monster.h"


#define PRIEST 498
#define MERCHANT 526
#define BANKER 495
#define GOBLIN 418
#define ZOMBIE 452
#define SPIDER 876
#define SKELETON 914

class ArgentumGame : public Thread {
public:
    //Instancia una nueva sala de Argentum
    ArgentumGame(const unsigned int room, std::ifstream &map_config);
    ~ArgentumGame() override;
    void run() override;
    const unsigned int get_room();
    void kill();
    void print_debug_map();

private:
    unsigned int room = 0;
    bool alive = true;
    Map *map;
    //actualiza el mundo
    //seconds es el tiempo que ha pasado en el server
    void update(unsigned long long seconds);
	void move_monsters();
    //segun los ids de la capa 2 del json generado por tiled,
    //coloca a los monstruos iniciales del mapa.
    void place_initial_monsters(Json::Value root);
	std::vector<BaseCharacter*> characters;
};

#endif //ARGENTUMGAME_H
