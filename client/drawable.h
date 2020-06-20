#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SDL2/SDL.h>

class Drawable {
 protected:
  // En que lugar de la imagen nos ubicamos
  int x;
  int y;
  // Porcion de la imagen
  int width;
  int height;

 public:
  virtual void render(int, int) = 0;
  virtual int get_width() const = 0;
  virtual int get_height() const = 0;
  virtual int get_x() const = 0;
  virtual int get_y() const = 0;
};

#endif
