#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include "sdl_window.h"

class SdlTexture {
    private:
        SDL_Texture* loadTexture(const std::string &filename);
        SDL_Renderer* renderer;
        SDL_Texture* texture;

    public:
        SdlTexture(const std::string &filename, SdlWindow& window);
 
        ~SdlTexture();
 
        void render() const;

};

#endif
