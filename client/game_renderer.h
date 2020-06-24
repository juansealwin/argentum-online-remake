#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL2/SDL.h>

#include <vector>
#include "protected_map.h"
#include "exception_messages.h"
#include "game.h"
#include "playable_character.h"
#include "sdl_exception.h"
#include "texture.h"
#include "thread.h"

class GameRenderer : public Thread {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int id_hero;
  bool is_running;
  int screen_width;
  int screen_height;
  PlayableCharacter& player;
  ProtectedMap& protected_map;
  Game* current_game;

 public:
  GameRenderer(int, int, PlayableCharacter&, ProtectedMap&);
  ~GameRenderer();
  void window_init();
  void run();
};

#endif