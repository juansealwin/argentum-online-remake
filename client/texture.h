#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "sdl_exception.h"
#include "exception_messages.h"

class Texture {
 private:
  SDL_Texture *texture;
  int width;
  int height;

 public:
  Texture();
  Texture(std::string, SDL_Renderer *);
  ~Texture();
  // Renderiza en un x, y determiando
  void render(SDL_Renderer *, int, int);
  // Renderiza la textura en un x e y concreto
  void render(SDL_Renderer *, SDL_Rect *, int, int);
  // Renderiza toda la textura en un viewport concreto
  void render(SDL_Renderer *, SDL_Rect *, SDL_Rect *);
  void load_texture(const char *, SDL_Renderer *);
  void load_from_rendered_text(SDL_Renderer *, TTF_Font*, std::string, SDL_Color);
  void free();
  int get_width() const;
  //int get_height() const;
};

#endif
