#include "character.h"

Character::~Character() {}

void Character::move(move_t move_type) {
  body_rect = animation_move.get_next_clip(move_type);
}

void Character::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  // Renderizamos el cuerpo principal
  texture_manager.get_texture(type_character)
      .render(renderer, &body_rect, x - x_rel, y - height / 2 - y_rel);

  if (spellbound.spell_alive()) 
    spellbound.render(renderer, x - x_rel, y - height / 2 - y_rel);
}

void Character::update_position(int new_x, int new_y, move_t orient) {
  orientation = orient;

  while (x / TILE_SIZE != new_x) {
    if (x / TILE_SIZE < new_x) {
      x += TILE_SIZE;
    } else {
      x -= TILE_SIZE;
    }
  }
  while (y / TILE_SIZE != new_y) {
    if (y / TILE_SIZE < new_y) {
      y += TILE_SIZE;
    } else {
      y -= TILE_SIZE;
    }
  }
  move(orient);
}

void Character::set_character_features(entity_t id) {
  // Lo seteamos de antemano porque en algunos personajes cambia
  body_rect.x = 0;
  body_rect.y = 0;

  switch (id) {
    case HUMAN:
      width = 25;
      height = 45;
      type_character = ID_HUMAN;
      walk = WALK_PC;
      break;

    case ELF:
      width = 25;
      height = 45;
      type_character = ID_ELF;
      walk = WALK_PC;
      break;

    case GNOME:
      width = 25;
      height = 45;
      type_character = ID_GNOME;
      walk = WALK_PC;
      break;

    case DWARF:
      width = 25;
      height = 45;
      type_character = ID_DWARF;
      walk = WALK_PC;
      break;

    case SPIDER:
      width = 53;
      height = 33;
      type_character = ID_SPIDER;
      walk = WALK_SPIDER;
      break;

    case SKELETON:
      width = 25;
      height = 52;
      type_character = ID_SKELETON;
      walk = WALK_SKELETON;
      break;

    case GOBLIN:
      width = 24;
      height = 33;
      type_character = ID_GOBLIN;
      walk = WALK_GOBLIN;
      break;

    case ZOMBIE:
      width = 25;
      height = 47;
      type_character = ID_ZOMBIE;
      walk = WALK_ZOMBIE;
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
      height = 46;
      type_character = ID_BANKER;
      break;

    default:
      break;
  }
  // Seteamos las dimensiones de la porcion a renderizar
  body_rect.w = width;
  body_rect.h = height;
}

sound_t Character::sound_walk() { return walk; }

void Character::set_spell(id_texture_t id_spell, int lifetime) {
  if (lifetime == 0)
    spellbound = Spell();
  else
    spellbound = Spell(id_spell, lifetime);
}

bool Character::change_position(int new_x, int new_y, move_t orient) {
  return !(x == new_x && y == new_y && orientation == orient);
}