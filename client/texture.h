#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL_image.h>

#include <string>

#include "drawable.h"
#include "sdl_exception.h"

class Texture {
 private:
  SDL_Texture* texture;
  int width;
  int height;

 public:
  Texture();

  ~Texture();

  // Renderiza la textura en un x e y concreto
  void render(SDL_Renderer*, SDL_Rect*, int, int);

  void render(SDL_Renderer*, SDL_Rect*, SDL_Rect*);

  void loadTexture(std::string, SDL_Renderer*);

  void free();

  int getWidth() const;

  int getHeight() const;
};

#endif
