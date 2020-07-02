#include "spell.h"

Spell::Spell() { life_time = 0; }

Spell::Spell(id_texture_t type, int time_left) {
  set_life_time(type);
  life_time = time_left;
}

Spell::Spell(const Spell& other_spell) {
  width = other_spell.width;
  height = other_spell.height;
  life_time = other_spell.life_time;
  spell_type = other_spell.spell_type;
  one_texture_animation = other_spell.one_texture_animation;
  if (!one_texture_animation) {
    animation_cast = other_spell.animation_cast;
    animation_frame = other_spell.animation_frame;
  }
}

Spell::~Spell() {}

Spell& Spell::operator=(const Spell& other_spell) {
  width = other_spell.width;
  height = other_spell.height;
  life_time = other_spell.life_time;
  spell_type = other_spell.spell_type;
  one_texture_animation = other_spell.one_texture_animation;
  if (!one_texture_animation) {
    animation_cast = other_spell.animation_cast;
    animation_frame = other_spell.animation_frame;
  }
  return *this;
}

void Spell::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  if (one_texture_animation)
    texture_manager.get_texture(spell_type)
        .render(renderer, &animation_frame, x - x_rel, y - height / 2 - y_rel);

  else
    texture_manager.get_texture(spell_type, life_time)
        .render(renderer, NULL, x_rel, y_rel);
}

void Spell::set_life_time(id_texture_t type) {
  switch (type) {
    case ID_MAGIC_ARROW:
      break;

    case ID_ELECTRIC_SHOCK:
      width = 128;
      height = 128;
      one_texture_animation = false;
      break;

    case ID_HEAL:
      break;

    case ID_EXPLOSION:
      width = 150;
      height = 150;
      one_texture_animation = false;
      break;
  }
  spell_type = type;
}

int Spell::spell_alive() { return life_time; }