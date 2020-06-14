#ifndef Player_H
#define Player_H

#include <string>
#include <vector>

#include "drawable.h"
#include "move.h"

class Player : public Drawable {
 protected:
  Texture body_texture;
  Texture head_texture;
  SDL_Renderer* renderer = NULL;
  Move* animation_move = NULL;
  SDL_Rect body_rect;
  SDL_Rect head_rect;
  int total_clips = 6;

 public:
  virtual ~Player();
  virtual void render() override;
  virtual void move(move_t);
  virtual void updateFaceProfile(move_t);
  virtual int getWidth() const override;
  virtual int getHeight() const override;
  virtual int getX() const override;
  virtual int getY() const override;
  virtual int getHeadW() const;
  virtual int getHeadH() const;
};

#endif
