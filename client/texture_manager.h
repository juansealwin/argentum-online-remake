#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>

#include <map>
#include <string>

#include "sound_effect.h"
#include "texture.h"
#include "types.h"

class TextureManager {
 private:
  std::map<id_texture_t, Texture*> map;
  TextureManager();

 public:
  SoundEffect borrame;
  ~TextureManager();
  void load_textures(SDL_Renderer*);
  Texture& get_texture(id_texture_t);
  Texture& get_texture(id_texture_t, int);
  TextureManager(const TextureManager&) = delete;
  static TextureManager& get_instance();
};

extern TextureManager& texture_manager;

#endif
