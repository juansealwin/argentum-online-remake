#include "texture.h"

Texture::Texture() {
  texture = NULL;
  width = 0;
  height = 0;
}

Texture::Texture(std::string path, SDL_Renderer* renderer) {
  load_texture(path.c_str(), renderer);
}

Texture::~Texture() { free(); }

void Texture::load_texture(const char* id_path, SDL_Renderer* renderer) {
  // La textura final
  SDL_Texture* new_texture = NULL;

  SDL_Surface* new_surface = IMG_Load(id_path);
  // texture = IMG_LoadTexture(renderer, filename.c_str());

  if (!new_surface)
    throw SdlException(MSG_ERROR_LOAD_TEXTURE, SDL_GetError());
  else {
    // Color key image
    SDL_SetColorKey(new_surface, SDL_TRUE,
                    SDL_MapRGB(new_surface->format, 0, 0, 0));

    // Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer, new_surface);

    if (!new_texture) {
      throw SdlException(MSG_ERROR_LOAD_TEXTURE, SDL_GetError());
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

void Texture::load_from_rendered_text(SDL_Renderer* renderer, TTF_Font* font,
                                      std::string texture_text,
                                      SDL_Color text_color) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface* textSurface =
      TTF_RenderText_Solid(font, texture_text.c_str(), text_color);
  if (textSurface == NULL) {
    throw SdlException(MSG_ERROR_LOAD_TEXTURE_TEXT, SDL_GetError());
  } else {
    // Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == NULL) {
      throw SdlException(MSG_ERROR_LOAD_TEXTURE_TEXT, SDL_GetError());
    } else {
      // Get image dimensions
      width = textSurface->w;
      height = textSurface->h;
    }
    // Get rid of old surface
    SDL_FreeSurface(textSurface);
  }
}

void Texture::render(SDL_Renderer* renderer, int x, int y) {
  SDL_Rect render_quad = {x, y, width, height};
  SDL_RenderCopy(renderer, texture, NULL, &render_quad);
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

int Texture::get_width(void) const { return width; }

//int Texture::get_height(void) const { return height; }
