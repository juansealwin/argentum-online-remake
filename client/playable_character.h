#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "character.h"
#include "item.h"
#include "sound_effect.h"
#include "spell.h"

class PlayableCharacter : public Character {
 protected:
  id_texture_t type_head;
  SDL_Rect head_rect;
  id_texture_t helmet;
  id_texture_t armor;
  id_texture_t shield;
  id_texture_t weapon;
  

 public:
  PlayableCharacter(character_t, int, int);
  PlayableCharacter(const PlayableCharacter&);
  PlayableCharacter& operator=(const PlayableCharacter&);
  ~PlayableCharacter();
  virtual void move(move_t) override;
  virtual void render(SDL_Renderer*, int, int) override;
  void update_face_profile(move_t);
  void render_as_hero(SDL_Renderer*);
  void equip_item(item_t, id_texture_t);
  void unequip_item(equipped_t);
  int set_head_dimensions(character_t);
  int get_head_w() const;
  int get_head_h() const;
};

#endif