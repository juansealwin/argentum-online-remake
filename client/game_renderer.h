#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL2/SDL.h>

#include <vector>

#include "exception_messages.h"
#include "map.h"
#include "sdl_exception.h"
#include "texture.h"
#include "thread.h"

class GameRenderer : public Thread {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  bool is_running;
  int screen_width;
  int screen_height;
  std::vector<Texture*> textures;
  PlayableCharacter& player;
  Map& current_map;

 public:
  GameRenderer(int, int, PlayableCharacter&, Map&);
  ~GameRenderer();
  void windowInit();
  void run();
};

#endif