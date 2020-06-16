#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

#include "drawable.h"
#include "move.h"

class Character : public Drawable {
 protected:
  Texture body_texture;
  Texture head_texture;
  SDL_Renderer* renderer = NULL;
  Move* animation_move = NULL;
  SDL_Rect body_rect;
  SDL_Rect head_rect;
  int half_screen_w;
  int half_screen_h;
  int total_clips = 6;

 public:
  virtual ~Character();
  virtual void render() override;
  virtual void move(move_t);
  virtual void updateFaceProfile(move_t);
  virtual void updatePosition(move_t );
  virtual int getWidth() const override;
  virtual int getHeight() const override;
  virtual int getX() const override;
  virtual int getY() const override;
  virtual int getHeadW() const;
  virtual int getHeadH() const;
};

#endif
