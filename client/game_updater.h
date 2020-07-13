#ifndef GAME_UPDATER_H
#define GAME_UPDATER_H

#include <SDL2/SDL.h>

#include <map>

#include "entity_status.h"
#include "common_socket.h"
#include "exception_messages.h"
#include "game.h"
#include "protected_map.h"
#include "protocol.h"
#include "sdl_exception.h"
#include "thread.h"
// Para el desserializar
#include "algorithm"

#define CLOSE_CONNECTION_NOTIFICATION 0
#define STATUS_NOTIFICATION 1
#define MAP_CHANGING_NOTIFICATION 3
#define MESSAGE_NOTIFICATION 4
#define BANKED_ITEMS_NOTIFICATION 5
#define SALE_ITEMS_NOTIFICATION 6

class GameUpdater : public Thread {
 private:
  int id_hero;
  ProtectedMap& protected_map;
  std::map<int, EntityStatus> next_status;
  UIStatus next_ui_status;
  bool& is_running;
  Socket& read_socket;
  std::vector<unsigned char> status_serialized;

 public:
  GameUpdater(int, ProtectedMap&, Socket&, bool&);
  ~GameUpdater();
  void run();
  void deserialize_status(unsigned int&);
  id_texture_t get_item_texture(int) const; 
  equipped_t get_type_equipped(int);
  map_t get_new_map(int);
};

#endif