#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H
#include <unistd.h>

#include <fstream>
#include <mutex>
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "../util/thread.h"
#include "../util/thread_safe_queue.h"
#include "base_character.h"
#include "map.h"
#include "monster.h"
#include "command.h" //<- guarda con esto y dependencias circulares
#include "move_command.h"
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
  ArgentumGame(const unsigned int room, ThreadSafeQueue<Command *> *commands_queue, std::ifstream &map_config);
  ~ArgentumGame() override;
  void run() override;
  unsigned int get_room();
  void kill();
  void print_debug_map();
  void move_entity(int entity_id, int x, int y);

 private:
  unsigned int room = 0;
  // A esta cola deberian tener acceso tambien los clientes conectados a esta
  // sala, cuando envian un comando nuevo se encolan y en cada update() del
  // juego se van procesando
  ThreadSafeQueue<Command *> *commands_queue;
  std::mutex mutex;
  std::string map_name;
  Map *map;
  bool alive = true;
  // actualiza el mundo segun los comandos recibidos
  // si recibe true, ademas,  aplica los cambios que se deberian aplicar pasado
  // un segundo
  void update(bool one_second_update);
  void auto_move_monsters();
  // segun los ids de la capa 2 del json generado por tiled,
  // coloca a los monstruos iniciales del mapa.
  void place_initial_monsters(Json::Value map_cfg);
  std::map<int, Entity *> entities;
  Json::Value game_status();
};

#endif  // ARGENTUMGAME_H