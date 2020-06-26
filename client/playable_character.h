#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "character.h"
#include "item.h"

class PlayableCharacter : public Character {
 protected:
  id_texture_t type_head;
  SDL_Rect head_rect;
  int half_screen_w;
  int half_screen_h;
  Item helmet;
  Item armor;
  Item shield;
  Item weapon;

 public:
  PlayableCharacter(character_t, int, int);
  PlayableCharacter(const PlayableCharacter&);
  PlayableCharacter& operator=(const PlayableCharacter&);
  ~PlayableCharacter();
  virtual void move(move_t) override;
  virtual void update_face_profile(move_t);
  virtual void render(SDL_Renderer*, int, int) override;
  virtual void render_as_hero(SDL_Renderer*);
  virtual int set_head_dimensions(character_t);
  virtual int get_head_w() const;
  virtual int get_head_h() const;
};

#endif