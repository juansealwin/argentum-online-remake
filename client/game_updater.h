#ifndef GAME_UPDATER_H
#define GAME_UPDATER_H

#include <SDL2/SDL.h>

#include <map>

#include "protected_map.h"
#include "character_status.h"
#include "exception_messages.h"
#include "game.h"
#include "sdl_exception.h"
#include "thread.h"
#include "common_socket.h"
#include "protocol.h"
//para el desserializar
#include "algorithm"

class GameUpdater : public Thread {
 private:
  ProtectedMap& protected_map;
  std::map<int, CharacterStatus> next_status;
  bool& is_running;
  Socket& read_socket;
  std::vector<unsigned char> status_serialized;

 public:
  GameUpdater(ProtectedMap&, Socket&, bool&);
  ~GameUpdater();
  void run();
  void deserialize_status();
};

#endif