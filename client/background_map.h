#ifndef BACKGROUND_MAP_H
#define BACKGROUND_MAP_H

#include <string>

#include "texture.h"
#define MAP_SIZE 3200

class BackgroundMap {
 private:
  Texture background_texture;
  SDL_Renderer* renderer;
  SDL_Rect map_piece;
  SDL_Rect viewport;
  int screen_width;
  int screen_height;

 public:
  BackgroundMap(std::string, SDL_Renderer*, int, int);
  ~BackgroundMap();
  void render();
  void update(int, int);
  void changeMap(std::string);
};

#endif