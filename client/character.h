#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "drawable.h"
#include "animation.h"
#include "sound_effect.h"
#include "spell.h"

class Character : public Drawable {
 protected:
  id_texture_t type_character;
  Animation animation_move;
  SDL_Rect body_rect;
  SoundEffect walk;
  Spell spellbound;

 public:
  virtual ~Character();
  virtual void render(SDL_Renderer*, int, int);
  virtual void move(move_t);
  virtual void update_position(int, int);
  virtual int set_character_features(entity_t);
  virtual void sound_walk();
  virtual void set_spell(id_texture_t, int);
  virtual bool change_position(int, int);
};

#endif
