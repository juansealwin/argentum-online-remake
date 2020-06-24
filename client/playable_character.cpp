#include "playable_character.h"

PlayableCharacter::PlayableCharacter(SDL_Renderer* ren, character_t id_char,
                                     int new_x, int new_y) {
  half_screen_w = new_x;
  half_screen_h = new_y;
  x = new_x;
  y = new_y;
  renderer = ren;
  set_character_dimensions(id_char);
  set_head_dimensions(id_char);
  animation_move = new Move(width, height, type_character);
  body_texture.load_texture(paths->get_path_texture(type_character), renderer);
  head_texture.load_texture(paths->get_path_texture(type_head), renderer);
}

PlayableCharacter::~PlayableCharacter() {
  delete animation_move;
  renderer = nullptr;
  // body_texture.free();
  // shead_texture.free();
}

// A los jugables hay que actualizarles el perfil
void PlayableCharacter::move(move_t move_type) {
  body_rect = animation_move->get_next_clip(move_type);
  update_face_profile(move_type);
}

void PlayableCharacter::update_face_profile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

// Creo que esta funcion se va a poder borrar
void PlayableCharacter::render_as_hero() {
  body_texture.render(renderer, &body_rect, half_screen_w - width / 2,
                      half_screen_h - height / 2);
  head_texture.render(renderer, &head_rect, half_screen_w - head_rect.w / 2,
                      half_screen_h - height / 2 - head_rect.h / 2);
}

void PlayableCharacter::render(int x_rel, int y_rel) {
  body_texture.render(renderer, &body_rect, x - width / 2 - x_rel,
                      y - height / 2 - y_rel);
  head_texture.render(renderer, &head_rect, x - head_rect.w / 2 - x_rel,
                      y - height / 2 - head_rect.h / 2 - y_rel);
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

int PlayableCharacter::get_head_w() const { return head_rect.w; }

int PlayableCharacter::get_head_h() const { return head_rect.h; }