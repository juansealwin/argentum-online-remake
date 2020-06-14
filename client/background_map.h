#ifndef BACKGROUND_MAP_H
#define BACKGROUND_MAP_H

#include <string>

#include "texture.h"

class BackgroundMap {
 private:
  Texture background_texture;
  SDL_Renderer* renderer;
  SDL_Rect map_piece;

 public:
  BackgroundMap(std::string, SDL_Renderer*);
  ~BackgroundMap();
  void render();
  void update(int, int);
  void changeMap(std::string);
};

#endif