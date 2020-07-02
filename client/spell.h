#ifndef SPELL_H
#define SPELL_H

#include "animation.h"
#include "drawable.h"

#define FRAMES_EXPLOSION 21

class Spell : public Drawable {
 private:
  id_texture_t spell_type;
  int life_time;
  Animation animation_cast;
  SDL_Rect animation_frame;
  bool alive;
  bool one_texture_animation;

 public:
  Spell();
  Spell(id_texture_t, int, int);
  ~Spell();
  virtual void render(SDL_Renderer*, int, int) override;
  void set_life_time(id_texture_t);
  bool spell_alive();
};

#endif