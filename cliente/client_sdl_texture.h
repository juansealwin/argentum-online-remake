#ifndef __CLIENT_SDL_TEXTURE_H__
#define __CLIENT_SDL_TEXTURE_H__
#include <string>
#include <SDL2/SDL_image.h>
#include "client_sdl_window.h"

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
