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
  float width_ratio;
  float height_ratio;

 public:
  ~TextureManager();
  void load_textures(SDL_Renderer*);
  Texture& get_texture(id_texture_t);
  Texture& get_texture(id_texture_t, int);
  TextureManager(const TextureManager&) = delete;
  static TextureManager& get_instance();
  void set_aspect_ratio(const float, const float);
  float get_w_ratio() const;
  float get_h_ratio() const;
};

extern TextureManager& texture_manager;

#endif
