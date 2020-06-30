#include "playable_character.h"



PlayableCharacter::PlayableCharacter(character_t id_char, int new_x, int new_y)
    : half_screen_w(new_x), half_screen_h(new_y) {
  x = new_x*TILE_SIZE;
  y = new_y*TILE_SIZE;
  set_character_dimensions(id_char);
  set_head_dimensions(id_char);
  animation_move = Animation(width, height, type_character);
  helmet = ID_NULL;
  armor = ID_NULL;
  weapon = ID_NULL;
  shield = ID_NULL;
  walk.set_sound("caminar.wav");
}

PlayableCharacter::PlayableCharacter(const PlayableCharacter& other_pc) {
  half_screen_w = other_pc.half_screen_w;
  half_screen_h = other_pc.half_screen_h;
  x = other_pc.x;
  y = other_pc.y;
  type_character = other_pc.type_character;
  // Colocamos las dimensiones del personaje
  width = other_pc.width;
  height = other_pc.height;
  body_rect = other_pc.body_rect;
  // Colocamos las dimensiones de su cabeza
  type_head = other_pc.type_head;
  head_rect = other_pc.head_rect;

  animation_move = other_pc.animation_move;
}

PlayableCharacter& PlayableCharacter::operator=(
    const PlayableCharacter& other_pc) {
  half_screen_w = other_pc.half_screen_w;
  half_screen_h = other_pc.half_screen_h;
  x = other_pc.x;
  y = other_pc.y;
  type_character = other_pc.type_character;
  // Colocamos las dimensiones del personaje
  width = other_pc.width;
  height = other_pc.height;
  body_rect = other_pc.body_rect;
  // Colocamos las dimensiones de su cabeza
  type_head = other_pc.type_head;
  head_rect = other_pc.head_rect;

  animation_move = other_pc.animation_move;
  return *this;
}

PlayableCharacter::~PlayableCharacter() {}

// A los jugables hay que actualizarles el perfil
void PlayableCharacter::move(move_t move_type) {
  body_rect = animation_move.get_next_clip(move_type);
  walk.play_sound(0);
  update_face_profile(move_type);
}

void PlayableCharacter::update_face_profile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

// Creo que esta funcion se va a poder borrar
void PlayableCharacter::render_as_hero(SDL_Renderer* renderer) {
  texture_manager.get_texture(type_character)
      .render(renderer, &body_rect, half_screen_w - width / 2,
              half_screen_h - height / 2);
  texture_manager.get_texture(type_head).render(
      renderer, &head_rect, half_screen_w - head_rect.w / 2,
      half_screen_h - height / 2 - head_rect.h / 2);
}

void PlayableCharacter::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  // Solo se renderiza la armadura o el cuerpo para no repetir manos y pies
  if (armor) {
    texture_manager.get_texture(armor)
        .render(renderer, &body_rect, x - x_rel,
                y - height / 2 - y_rel);
  } else {
    texture_manager.get_texture(type_character)
        .render(renderer, &body_rect, x - x_rel,
                y - height / 2 - y_rel);
  }
  // Renderizamos cabeza
  texture_manager.get_texture(type_head).render(
      renderer, &head_rect, x + head_rect.w / 4 - x_rel,
      y - height / 2 - head_rect.h / 2 - y_rel);

  // Si tiene el casco equipado lo renderizamos
  if (helmet) {
    texture_manager.get_texture(helmet)
        .render(renderer, &head_rect, x + head_rect.w / 4 - x_rel,
                y - height / 2 - head_rect.h / 2 - y_rel);
  }

  // Si tiene el arma equipada la renderizamos
  if (weapon) {
    texture_manager.get_texture(weapon)
        .render(renderer, &body_rect, x - width / 2 - x_rel,
                y - height / 2 - y_rel);
  }
}

int PlayableCharacter::set_head_dimensions(character_t id) {
  switch (id) {
    case HUMAN:
      head_rect = {0, 0, 17, 16};
      type_head = ID_HUMAN_HEAD;
      break;

    case ELF:
      head_rect = {0, 0, 17, 16};
      type_head = ID_ELF_HEAD;
      break;

    case GNOME:
      head_rect = {0, 0, 17, 17};
      type_head = ID_GNOME_HEAD;
      break;

    case DWARF:
      head_rect = {0, 0, 17, 17};
      type_head = ID_DWARF_HEAD;
      break;
  }
}

void PlayableCharacter::unequip_item(item_t id) {
  // Reinicializamos el item para que no tenga valores dentro
  switch (id) {
    case HELMET:
      helmet = ID_NULL;
      break;

    case ARMOR:
      armor = ID_NULL;
      break;

    case SHIELD:
      shield = ID_NULL;
      break;

    case WEAPON:
      weapon = ID_NULL;
      break;
  }
}

void PlayableCharacter::equip_item(item_t item, id_texture_t id) {
  // Reinicializamos el item para que no tenga valores dentro
  switch (item) {
    case HELMET:
      helmet = id;
      break;

    case ARMOR:
      armor = id;
      break;

    case SHIELD:
      shield = id;
      break;

    case WEAPON:
      weapon = id;
      break;
  }
}

int PlayableCharacter::get_head_w() const { return head_rect.w; }

int PlayableCharacter::get_head_h() const { return head_rect.h; }