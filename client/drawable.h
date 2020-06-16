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
  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
  virtual int getX() const = 0;
  virtual int getY() const = 0;
};

#endif
