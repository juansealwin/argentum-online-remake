#ifndef GAME_UPDATER_H
#define GAME_UPDATER_H

#include <SDL2/SDL.h>

#include <map>

#include "blockingmap.h"
#include "character_status.h"
#include "map.h"
#include "thread.h"

class GameUpdater : public Thread {
 private:
  BlockingMap& map_updated;
  SDL_Renderer* next_renderer;
  SDL_Renderer* current_renderer;
  Map& current_map;
  std::map<int, CharacterStatus> next_map;
  bool is_running;

 public:
  GameUpdater(BlockingMap&, Map&);
  ~GameUpdater();
  void run();
};

#endif