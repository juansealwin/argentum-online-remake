#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SDL2/SDL.h>

class Drawable {
   protected:
    //En que lugar de la imagen nos ubicamos
    int x;
    int y;
    //Porcion de la imagen
    int width;
    int height;

   public:
    virtual void render(SDL_Renderer *, SDL_Rect*, int, int) = 0;
    virtual int getWidth(void) const = 0;
    virtual int getHeight(void) const = 0;
    virtual int getX(void) const = 0;
    virtual int getY(void) const = 0;
    virtual void setX(int) = 0;
    virtual void setY(int) = 0;
};


#endif