#include "texture.h"

Texture::Texture() {
  texture = NULL;
  width = 0;
  height = 0;
}

Texture::~Texture() { free(); }

void Texture::loadTexture(int id_path, SDL_Renderer* renderer) {
  // Libera la textura si ya tenia algo cargado
  free();
  
  // La textura final
  SDL_Texture* new_texture = NULL;

  SDL_Surface* new_surface = IMG_Load(texture_paths.getPathTexture(id_path));
  // texture = IMG_LoadTexture(renderer, filename.c_str());

  if (!new_surface)
    throw SdlException("Error al cargar la textura", SDL_GetError());
  else {
    // Color key image
    SDL_SetColorKey(new_surface, SDL_TRUE,
                    SDL_MapRGB(new_surface->format, 0, 0, 0));

    // Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);
    if (!new_texture) {
      throw SdlException("Error al cargar la textura", SDL_GetError());
    } else {
      // Cargamos las dimensiones de la imagen
      width = new_surface->w;
      height = new_surface->h;
    }
    // Liberamos la surface
    SDL_FreeSurface(new_surface);
  }
  texture = new_texture;
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, int x_dest,
                     int y_dest) {
  SDL_Rect quad_dest = {x_dest, y_dest, width, height};
  // Checkeamos si queremos renderizar toda la textura o una porción

  if (clip != NULL) {
    quad_dest.h = clip->h;
    quad_dest.w = clip->w;
  }

  if (SDL_RenderCopy(renderer, texture, clip, &quad_dest))
    throw SdlException("Error al renderizar la textura", SDL_GetError());
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* dest) {
  if (SDL_RenderCopy(renderer, texture, clip, dest))
    throw SdlException("Error al renderizar la textura", SDL_GetError());
}

void Texture::free() {
  // Free texture if it exists
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    width = 0;
    height = 0;
  }
}

int Texture::getWidth(void) const { return width; }

int Texture::getHeight(void) const { return height; }
