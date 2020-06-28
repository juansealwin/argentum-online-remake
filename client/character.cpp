#include "character.h"

Character::~Character() {}

void Character::move(move_t move_type) {
  body_rect = animation_move.get_next_clip(move_type);
}

void Character::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  texture_manager.get_texture(type_character)
      .render(renderer, &body_rect, x - width / 2 - x_rel,
              y - height / 2 - y_rel);
}

void Character::update_position(int new_x, int new_y) {
  move_t move_type;
  while (x != new_x) {
    if (x < new_x) {
      x += TILE_SIZE;
      move_type = MOVE_RIGHT;
    } else {
      x -= TILE_SIZE;
      move_type = MOVE_LEFT;
    }
  }
  while (y != new_y) {
    if (y < new_y) {
      y += TILE_SIZE;
      move_type = MOVE_DOWN;
    } else {
      y -= TILE_SIZE;
      move_type = MOVE_UP;
    }
  }
  move(move_type);
}

int Character::set_character_dimensions(character_t id) {
  // Lo seteamos de antemano porque en algunos personajes cambia
  body_rect.x = 0;
  body_rect.y = 0;

  switch (id) {
    case HUMAN:
      width = 25;
      height = 45;
      type_character = ID_HUMAN;
      break;

    case ELF:
      width = 25;
      height = 45;
      type_character = ID_ELF;
      break;

    case GNOME:
      width = 25;
      height = 45;
      // Esto se debe a que el grafico es distinto
      body_rect.y = 10;
      type_character = ID_GNOME;
      break;

    case DWARF:
      width = 25;
      height = 45;
      // Esto se debe a que el grafico es distinto
      body_rect.y = 10;
      type_character = ID_DWARF;
      break;

    case SPIDER:
      width = 53;
      height = 33;
      type_character = ID_SPIDER;
      break;

    case SKELETON:
      width = 25;
      height = 52;
      type_character = ID_SKELETON;
      break;

    case GOBLIN:
      width = 24;
      height = 33;
      type_character = ID_GOBLIN;
      break;

    case ZOMBIE:
      width = 25;
      height = 47;
      type_character = ID_ZOMBIE;
      break;

    case PRIEST:
      width = 25;
      height = 45;
      type_character = ID_PRIEST;
      break;

    case MERCHANT:
      width = 23;
      height = 48;
      type_character = ID_MERCHANT;
      break;

    case BANKER:
      width = 25;
      height = 33;
      type_character = ID_BANKER;
      break;
  }
  // Seteamos las dimensiones de la porcion a renderizar
  body_rect.w = width;
  body_rect.h = height;
}