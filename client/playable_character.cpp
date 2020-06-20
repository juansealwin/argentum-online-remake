#include "playable_character.h"

PlayableCharacter::~PlayableCharacter() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
  head_texture.free();
}

void PlayableCharacter::move(move_t move_type) {
  body_rect = animation_move->get_next_clip(move_type);
  update_face_profile(move_type);
}

void PlayableCharacter::update_face_profile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

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

int PlayableCharacter::get_head_w() const { return head_rect.w; }

int PlayableCharacter::get_head_h() const { return head_rect.h; }