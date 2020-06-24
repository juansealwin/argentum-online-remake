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

class GameUpdater : public Thread {
 private:
  ProtectedMap& protected_map;
  std::map<int, CharacterStatus> next_status;
  bool is_running;
  Socket& read_socket;

 public:
  GameUpdater(ProtectedMap&, Socket&);
  ~GameUpdater();
  void run();
};

#endif