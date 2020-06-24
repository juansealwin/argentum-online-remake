#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>

#include <map>
#include <string>

#include "texture.h"
#include "types.h"

class TextureManager {
 private:
  SDL_Renderer* renderer;
  static TextureManager* instance_texture_manager;
  TextureManager();
  std::map<id_texture_t, Texture> map;

 public:
  static TextureManager* get_instance();
  ~TextureManager();
  Texture& get_texture(id_texture_t);
};

extern TextureManager* texture_manager;

#endif
