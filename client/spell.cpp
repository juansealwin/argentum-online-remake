#include "spell.h"

Spell::Spell() { life_time = 0; }

Spell::Spell(id_texture_t type, int time_left) {
  life_time = time_left;
  set_features(type);
}

Spell::Spell(const Spell& other_spell) {
  x = other_spell.x;
  y = other_spell.y;
  width = other_spell.width;
  height = other_spell.height;
  life_time = other_spell.life_time;
  spell_type = other_spell.spell_type;
  one_texture_animation = other_spell.one_texture_animation;
  if (one_texture_animation) {
    animation_cast = other_spell.animation_cast;
    animation_frame = other_spell.animation_frame;
  }
  max_life_time = other_spell.max_life_time;
}

Spell::~Spell() {}

Spell& Spell::operator=(const Spell& other_spell) {
  x = other_spell.x;
  y = other_spell.y;
  width = other_spell.width;
  height = other_spell.height;
  life_time = other_spell.life_time;
  spell_type = other_spell.spell_type;
  one_texture_animation = other_spell.one_texture_animation;
  if (one_texture_animation) {
    animation_cast = other_spell.animation_cast;
    animation_frame = other_spell.animation_frame;
  }
  max_life_time = other_spell.max_life_time;
  return *this;
}

void Spell::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  if (one_texture_animation) {
    animation_cast = Animation(width, height, spell_type);
    animation_frame = animation_cast.get_next_clip(life_time, max_life_time);
    texture_manager.get_texture(spell_type)
        .render(renderer, &animation_frame, x + x_rel - width / 4,
                y + y_rel - height / 2);
  } else {
    texture_manager.get_texture(spell_type, life_time)
        .render(renderer, NULL, x_rel - width / 2, y_rel - height);
  }
}

void Spell::set_features(id_texture_t type) {
  spell_type = type;
  x = 0;
  y = 0;
  switch (type) {
      // No son las dimensiones exactas ya que en la imagen hay sobrantes
    case ID_BLEEDING:
      width = 10;
      height = 0;
      one_texture_animation = false;
      max_life_time = FRAMES_BLEEDING * FRAMES_PER_TEXTURE;
      break;

    case ID_MAGIC_ARROW:
      x = 10;
      y = 15;
      width = 15;
      height = 15;
      one_texture_animation = true;
      max_life_time = FRAMES_BLEEDING * FRAMES_PER_TEXTURE;
      break;

    case ID_HEAL:
      width = 80;
      height = 85;
      one_texture_animation = true;
      max_life_time = FRAMES_HEAL * FRAMES_PER_TEXTURE;
      break;

    case ID_ELECTRIC_SHOCK:
      width = 107;
      height = 75;
      one_texture_animation = false;
      max_life_time = FRAMES_EXPLOSION * FRAMES_PER_TEXTURE;
      break;

    case ID_EXPLOSION:
      width = 120;
      height = 90;
      one_texture_animation = false;
      max_life_time = FRAMES_EXPLOSION * FRAMES_PER_TEXTURE;
      break;

    default:
      break;
  }
}

int Spell::spell_alive() { return life_time; }