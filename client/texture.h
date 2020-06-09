#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include "sdl_window.h"
#include "drawable.h"

class Texture : public Drawable{
    private:
        SDL_Texture* texture;
        

    public:
      Texture();

      ~Texture();

      //Renderiza toda la texutra
      void render(SDL_Renderer*) const;

      //Renderiza la textura en un x e y concreto
      virtual void render(SDL_Renderer*, int, int);

      //Renderiza una porción de la textura en un x e y concreto
      void render(SDL_Renderer*, int, int, int, int) const;

      void loadTexture(const std::string &, SDL_Renderer*);
    
      virtual int getWidth() const;
      
      virtual int getHeight() const;
      
      virtual int getX() const;
      
      virtual int getY() const;
      
      virtual void setX(int);

      virtual void setY(int);
      //void loadFromFile(std::string, SDL_Renderer*);

};

#endif
