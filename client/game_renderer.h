#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "thread.h"
#include "exception_messages.h"
#include "sdl_exception.h"
#include "texture.h"
#include "map.h"
#include <SDL2/SDL.h>
#include <vector>

class GameRenderer : public Thread{
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool is_running;
  int screen_width;
  int screen_height;
  std::vector<Texture*> textures;
  PlayableCharacter* player;
  Map* current_map;
  //Protocol* courier;

 
 public:
  GameRenderer(int, int);
  ~GameRenderer();
  void windowInit();
  void run();
};



#endif