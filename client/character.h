#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "drawable.h"
#include "move.h"

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
  int id;
  Texture body_texture;
  SDL_Renderer* renderer = NULL;
  Move* animation_move = NULL;
  SDL_Rect body_rect;

 public:
  virtual ~Character();
  virtual void render(int, int) override;
  virtual void move(move_t);
  virtual void update_position(int, int);
  virtual int get_width() const override;
  virtual int get_height() const override;
  virtual int get_x() const override;
  virtual int get_y() const override;
  virtual int get_id() const;
};

#endif
