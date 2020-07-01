#include "spell.h"

Spell::Spell() {}

Spell::Spell(id_texture_t type, int new_x, int new_y) {
  x = new_x * TILE_SIZE;
  y = new_y * TILE_SIZE;
  set_life_time(type);
}

Spell::~Spell() {}

void Spell::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  if (one_texture_animation)
    texture_manager.get_texture(spell_type)
        .render(renderer, &animation_frame, x - x_rel, y - height / 2 - y_rel);

  else
    texture_manager.get_texture(spell_type, life_time)
        .render(renderer, NULL, NULL);

  life_time--;
  // Borrame
  if (!life_time) life_time = FRAMES_PER_TEXT_EXPLOSION * FRAMES_EXPLOSION;
}

void Spell::set_life_time(id_texture_t type) {
  switch (type) {
    case ID_MAGIC_ARROW:
      break;

    case ID_ELECTRIC_SHOCK:
      break;

    case ID_HEAL:
      break;

    case ID_EXPLOSION:
      width = 150;
      height = 150;
      life_time = FRAMES_PER_TEXT_EXPLOSION * FRAMES_EXPLOSION;
      one_texture_animation = false;
      break;
  }
  spell_type = type;
}