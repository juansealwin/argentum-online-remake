#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "drawable.h"
#include "move.h"
#include "paths.h"

typedef enum {
  HUMAN = 0,
  ELF,
  GNOME,
  DWARF,
  SPIDER,
  GOBLIN,
  ZOMBIE,
  SKELETON,
  MERCHANT,
  BANKER,
  PRIEST
} character_t;

class Character : public Drawable {
 protected:
  int type_character;
  Texture body_texture;
  SDL_Renderer* renderer = NULL;
  Move* animation_move = NULL;
  SDL_Rect body_rect;

 public:
  virtual ~Character();
  virtual void render(int, int) override;
  virtual void move(move_t);
  virtual void update_position(int, int);
  virtual int set_character_dimensions(character_t);
};

#endif
