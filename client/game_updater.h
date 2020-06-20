#ifndef GAME_UPDATER_H
#define GAME_UPDATER_H

#include <SDL2/SDL.h>

#include <map>

#include "blocking_map.h"
#include "character_status.h"
#include "exception_messages.h"
#include "map.h"
#include "sdl_exception.h"
#include "thread.h"

class GameUpdater : public Thread {
 private:
  //Esto deberia ir en el GameRenderer
  SDL_Window* window;
  SDL_Renderer* renderer;
  int screen_width;
  int screen_height;
  int id_hero;

  // Esto es del GameUpdater
  BlockingMap& blocking_map;
  // SDL_Renderer* next_renderer;
  Map* current_map;
  std::map<int, CharacterStatus> next_status;
  std::map<int, CharacterStatus> current_status;
  bool is_running;

 public:
  GameUpdater(int, int, int, BlockingMap&);
  ~GameUpdater();
  void run();
  void windowInit();
};

#endif