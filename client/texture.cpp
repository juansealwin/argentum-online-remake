#include "texture.h"

Texture::Texture() { 
  texture = NULL;
  x = 0;
  y = 0;
  width = 0;
  height = 0;
}

Texture::~Texture() { SDL_DestroyTexture(texture); }

/*
void Texture::loadFromFile(std::string path, SDL_Renderer* renderer) {

        // Cargamos la surface en el path indicado
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL) {
    throw View::Exception("%s %s. %s: %s", ERR_MSG_LOAD_IMAGE, path.c_str(),
"SDL_IMG_Load() ", IMG_GetError()); } else {
                //Color key image
                SDL_SetColorKey(loadedSurface, SDL_TRUE,
SDL_MapRGB(loadedSurface->format, 0x80, 0x80, 0xBE));

                //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
                if (newTexture == NULL) {
      throw View::Exception("%s %s. %s: %s", ERR_MSG_CREATE_TEXTURE,
path.c_str(), "SDL_CreateTextureFromSurface() ", SDL_GetError()); } else {
                        // Cargamos las dimensiones de la imagen
                        this->width = loadedSurface->w;
                        this->height = loadedSurface->h;
                }
                // Liberamos la surface
                SDL_FreeSurface( loadedSurface );
        }

        //Return success
        this->texture = newTexture;
}
*/
void Texture::loadTexture(const std::string& path_file, SDL_Renderer* renderer) {
    
    SDL_Surface* new_surface = IMG_Load(path_file.c_str());
    //texture = IMG_LoadTexture(renderer, filename.c_str());

    if (!new_surface)
      throw SdlException("Error al cargar la textura", SDL_GetError());
    else {
      //Color key image
      SDL_SetColorKey(new_surface, SDL_TRUE, SDL_MapRGB(new_surface->format, 0x80, 0x80, 0xBE));

      //Create texture from surface pixels
      texture = SDL_CreateTextureFromSurface(renderer, new_surface);
      if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
      } else {
      //Cargamos las dimensiones de la imagen
        width = new_surface->w;
        height = new_surface->h;
      }
      //Liberamos la surface
      SDL_FreeSurface(new_surface);
    }    
}

void Texture::render(SDL_Renderer* renderer) const {
    if (SDL_RenderCopy(renderer, texture, NULL, NULL))
        throw SdlException("Error al renderizar la textura", SDL_GetError());
}

//esta no la voy a usar por ahora
void Texture::render(SDL_Renderer* renderer, int x_dest, int y_dest){
    SDL_Rect rect_dest = {x_dest, y_dest, x, y};
    if (SDL_RenderCopy(renderer, texture, NULL, &rect_dest))
        throw SdlException("Error al renderizar la textura", SDL_GetError());
}

void Texture::render(SDL_Renderer* renderer, int x_dest, int y_dest, int width_ren, int height_ren) const {
  SDL_Rect rect_src = {x, y, width_ren, height_ren};
  SDL_Rect rect_dest = {x_dest, y_dest, width_ren, height_ren};

  if (SDL_RenderCopy(renderer, texture, &rect_src, &rect_dest))
    throw SdlException("Error al renderizar la textura", SDL_GetError());
}

int Texture::getWidth(void) const {
	return width;
}

int Texture::getHeight(void) const {
	return height;
}

int Texture::getX(void) const {
	return x;
}

int Texture::getY(void) const {
	return y;
}

void Texture::setX(int new_x) {
	x = new_x;
}

void Texture::setY(int new_y) {
	y = new_y;
}