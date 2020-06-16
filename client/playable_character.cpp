#include "playable_character.h"

PlayableCharacter::~PlayableCharacter() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
  head_texture.free();
}

void PlayableCharacter::move(move_t move_type) {
  body_rect = animation_move->getNextClip(move_type);
  updateFaceProfile(move_type);
  updatePosition(move_type);
}

void PlayableCharacter::updateFaceProfile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

void PlayableCharacter::renderAsHero() {
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

int PlayableCharacter::getHeadW() const { return head_rect.w; }

int PlayableCharacter::getHeadH() const { return head_rect.h; }