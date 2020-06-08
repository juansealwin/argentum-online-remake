#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include "sdl_window.h"

class Texture {
    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Texture* loadTexture(const std::string &filename);

    public:
        Texture(const std::string &filename, SdlWindow& window);
 
        ~Texture();
 
        void render() const;

};

#endif
