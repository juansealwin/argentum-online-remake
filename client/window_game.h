#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "sdl_exception.h"
#include "texture.h"
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

class WindowGame {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int screen_width;
  int screen_height;
  bool full_screen;

 public:
  WindowGame();
  ~WindowGame();
  void window_init();
  SDL_Window* get_window();
  SDL_Renderer* get_renderer();
  void resize_screen(int, int, bool);
  int get_screen_width();
  int get_screen_height();
  bool get_full_screen_mode();
  float get_width_ratio();
  float get_height_ratio();
};

#endif