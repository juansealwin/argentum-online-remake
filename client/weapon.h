#ifndef WEAPON_H
#define WEAPON_H

#include "drawable.h"
#include "types.h"
#include "animation.h"

class Weapon : public Drawable {
 private:
  id_texture_t weapon_type;
  id_texture_t weapon_equipped;
  Animation animation_equipped;
  SDL_Rect frame_equipped;
  bool is_equipped;

 public:
  Weapon(id_texture_t, int, int);
  ~Weapon();
  virtual void render(SDL_Renderer*, int, int) override;
  void render_equiped(SDL_Renderer*, int, int);
  void set_weapon_dimensions(id_texture_t );
  void get_next_frame(move_t);
};

#endif