#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "types.h"
#include "drawable.h"
#include "move.h"
#include "texture_manager.h"

class Character : public Drawable {
 protected:
  id_texture_t type_character;
  Move animation_move;
  SDL_Rect body_rect;

 public:
  virtual ~Character();
  virtual void render(SDL_Renderer*, int, int) override;
  virtual void move(move_t);
  virtual void update_position(int, int);
  virtual int set_character_dimensions(character_t);
};

#endif
