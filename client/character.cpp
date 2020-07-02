#include "character.h"

Character::~Character() {}

void Character::move(move_t move_type) {
  body_rect = animation_move.get_next_clip(move_type);
}

void Character::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  // Renderizamos el cuerpo principal
  texture_manager.get_texture(type_character)
      .render(renderer, &body_rect, x - x_rel, y - height / 2 - y_rel);
  
  // Si esta afectado por algún hechizo lo renderizamos
  //if(spellbound.spell_alive())
    //spellbound.render(renderer, x - x_rel, y - height / 2 - y_rel);
}

void Character::update_position(int new_x, int new_y) {
  move_t move_type;
  while (x / TILE_SIZE != new_x) {
    if (x / TILE_SIZE < new_x) {
      x += TILE_SIZE;
      move_type = MOVE_RIGHT;
    } else {
      x -= TILE_SIZE;
      move_type = MOVE_LEFT;
    }
  }
  while (y / TILE_SIZE != new_y) {
    if (y / TILE_SIZE < new_y) {
      y += TILE_SIZE;
      move_type = MOVE_DOWN;
    } else {
      y -= TILE_SIZE;
      move_type = MOVE_UP;
    }
  }
  move(move_type);
}

int Character::set_character_features(character_t id) {
  // Lo seteamos de antemano porque en algunos personajes cambia
  body_rect.x = 0;
  body_rect.y = 0;

  switch (id) {
    case HUMAN:
      width = 25;
      height = 45;
      type_character = ID_HUMAN;
      walk.set_sound("caminar.wav");
      break;

    case ELF:
      width = 25;
      height = 45;
      type_character = ID_ELF;
      walk.set_sound("caminar.wav");
      break;

    case GNOME:
      width = 25;
      height = 45;
      // Esto se debe a que el grafico es distinto
      body_rect.y = 10;
      type_character = ID_GNOME;
      walk.set_sound("caminar.wav");
      break;

    case DWARF:
      width = 25;
      height = 45;
      // Esto se debe a que el grafico es distinto
      body_rect.y = 10;
      type_character = ID_DWARF;
      walk.set_sound("caminar.wav");
      break;

    case SPIDER:
      width = 53;
      height = 33;
      type_character = ID_SPIDER;
      walk.set_sound("caminar_araña.wav");
      break;

    case SKELETON:
      width = 25;
      height = 52;
      type_character = ID_SKELETON;
      walk.set_sound("caminar_esqueleto.wav");
      break;

    case GOBLIN:
      width = 24;
      height = 33;
      type_character = ID_GOBLIN;
      walk.set_sound("caminar_goblin.wav");
      break;

    case ZOMBIE:
      width = 25;
      height = 47;
      type_character = ID_ZOMBIE;
      walk.set_sound("caminar_zombie.wav");
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
  }
  // Seteamos las dimensiones de la porcion a renderizar
  body_rect.w = width;
  body_rect.h = height;
}

void Character::sound_walk() { walk.play_sound(0); }

void Character::set_spell(id_texture_t id_spell) {
  spellbound = Spell(id_spell, x, y);
}