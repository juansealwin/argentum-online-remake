#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include "character.h"
#include "sound_effect.h"
#include "spell.h"

#define GHOST_WIDTH 29
#define GHOST_HEIGHT 32
#define ZEN_WIDTH 31
#define ZEN_HEIGHT 68

class PlayableCharacter : public Character {
 protected:
  id_texture_t type_head;
  SDL_Rect head_rect;
  bool zen_mode;
  SDL_Rect meditating_frame;
  Animation meditating_animation;
  bool ghost;
  SDL_Rect ghost_body;
  Animation ghost_frame;
  id_texture_t helmet;
  id_texture_t armor;
  id_texture_t shield;
  id_texture_t weapon;
  Animation armor_animation;
  Animation shield_animation;
  Animation weapon_animation;
  SDL_Rect frame_equipped_h;
  SDL_Rect frame_equipped_a;
  SDL_Rect frame_equipped_s;
  SDL_Rect frame_equipped_w;

 public:
  PlayableCharacter(entity_t, int, int, move_t, bool, id_texture_t,
                    id_texture_t, id_texture_t, id_texture_t);
  PlayableCharacter(const PlayableCharacter&);
  PlayableCharacter& operator=(const PlayableCharacter&);
  ~PlayableCharacter();
  virtual void move(move_t) override;
  virtual void render(SDL_Renderer*, int, int) override;
  void update_face_profile(move_t);
  void render_as_hero(SDL_Renderer*);
  void equip_item(equipped_t, id_texture_t);
  void unequip_item(equipped_t);
  void set_head_dimensions(entity_t);
  void update_equipment(bool, bool, id_texture_t, id_texture_t, id_texture_t,
                        id_texture_t, std::vector<sound_t>&);
  void set_item_dimensions(id_texture_t id);
};

#endif