#include "client_sdl_texture.h"

SdlTexture::SdlTexture(const std::string &filename, SdlWindow& window)
    : renderer(window.getRenderer()) {
    texture = loadTexture(filename);
}

SdlTexture::~SdlTexture() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* SdlTexture::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(renderer,
                                           filename.c_str());
    if (!texture)
        throw SdlException("Error al cargar la textura", SDL_GetError());
    
    return texture;
}

void SdlTexture::render() const {
    if(SDL_RenderCopy(renderer, texture, NULL, NULL))
        throw SdlException("Error al renderizar la textura", SDL_GetError());
}