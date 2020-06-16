#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "drawable.h"
#include "move.h"

class Character : public Drawable {
 protected:
  Texture body_texture;
  SDL_Renderer* renderer = NULL;
  Move* animation_move = NULL;
  SDL_Rect body_rect;

 public:
  virtual ~Character();
  virtual void render(int, int) override;
  virtual void move(move_t);
  virtual void updatePosition(move_t);
  virtual int getWidth() const override;
  virtual int getHeight() const override;
  virtual int getX() const override;
  virtual int getY() const override;
};

#endif
