#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "sdl_exception.h"
#include "texture.h"

class WindowGame {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int screen_width;
  int screen_height;

 public:
  WindowGame();
  ~WindowGame();
  void window_init();
  SDL_Renderer* get_renderer();
};

#endif