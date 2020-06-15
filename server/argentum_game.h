#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H
#include <unistd.h>

#include <fstream>
#include <vector>

#include "../util/json/json.h"
#include "../util/json/json-forwards.h"
#include "../util/thread.h"
#include "base_character.h"
#include "map.h"
#include "monster.h"
#include <mutex>
#include "command.h"

#define PRIEST 1334
#define MERCHANT 1320
#define BANKER 1352
#define GOBLIN 1677
#define ZOMBIE 1288
#define SPIDER 1712
#define SKELETON 1750

class ArgentumGame : public Thread {
 public:
  // Instancia una nueva sala de Argentum
  ArgentumGame(const unsigned int room, std::ifstream &map_config);
  ~ArgentumGame() override;
  void run() override;
  unsigned int get_room();
  void kill();
  void print_debug_map();

 private:
  unsigned int room = 0;
  std::mutex mutex;
  std::string map_name;
  bool alive = true;
  Map *map;
  // actualiza el mundo
  // seconds es el tiempo que ha pasado en el server
  void update(bool one_second_update);
  void move_monsters();
  // segun los ids de la capa 2 del json generado por tiled,
  // coloca a los monstruos iniciales del mapa.
  void place_initial_monsters(Json::Value map_cfg);
  //std::vector<BaseCharacter *> characters;
  std::map<int, Entity *> entities;
  Json::Value game_status();

};

#endif  // ARGENTUMGAME_H
