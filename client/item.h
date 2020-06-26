#ifndef ITEM_H
#define ITEM_H

#include "animation.h"
#include "drawable.h"
#include "types.h"

class Item : public Drawable {
 private:
  id_texture_t item_type;
  id_texture_t item_equipped;
  id_texture_t item_equipped_xs;
  bool size_xs;
  Animation animation_equipped;
  SDL_Rect frame_equipped;
  bool is_equipped;

 public:
  Item();
  Item(id_texture_t, int, int);
  ~Item();
  virtual void render(SDL_Renderer*, int, int) override;
  void render_weapon_equipped(SDL_Renderer*, int, int);
  void set_item_dimensions(id_texture_t);
  void get_next_frame(move_t);
  bool equiped();
  id_texture_t get_texture(id_texture_t);
};

#endif