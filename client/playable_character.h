#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "character.h"

class PlayableCharacter : public Character {
 protected:
  Texture head_texture;
  SDL_Rect head_rect;
  int half_screen_w;
  int half_screen_h;

 public:
  ~PlayableCharacter();
  virtual void move(move_t) override;
  virtual void updateFaceProfile(move_t);
  virtual void render(int, int) override;
  virtual void renderAsHero();
  virtual int getHeadW() const;
  virtual int getHeadH() const;
};

#endif