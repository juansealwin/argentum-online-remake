#ifndef LOBBY_H
#define LOBBY_H

#include <SDL2/SDL.h>

#include "texture.h"

class Lobby {
 private:
  Texture log_in;
  Texture character_selection;
  SDL_Renderer* renderer;

 public:
  Lobby(SDL_Renderer*);
  ~Lobby();
  void start_lobby();
};

#endif
