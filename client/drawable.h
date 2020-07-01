#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL2/SDL.h>

#include "texture_manager.h"
#include "types.h"

#define TILE_SIZE 32

class Drawable {
 protected:
  // En que lugar de la imagen nos ubicamos
  int x;
  int y;
  // Porcion de la imagen
  int width;
  int height;

 public:
  virtual void render(SDL_Renderer*, int, int) = 0;
  virtual int get_width() const;
  virtual int get_height() const;
  virtual int get_x() const;
  virtual int get_y() const;
};

#endif
