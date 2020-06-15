#include "player.h"

Player::~Player() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
  head_texture.free();
}

void Player::move(move_t move_type) {
  body_rect = animation_move->getNextClip(move_type);
}

void Player::updateFaceProfile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

void Player::render() {
  body_texture.render(renderer, &body_rect, x - width / 2, y - height / 2);
  head_texture.render(renderer, &head_rect, x - head_rect.w / 2,
                      y - height / 2 - head_rect.h / 2 );
}

int Player::getWidth() const { return width; }

int Player::getHeight() const { return height; }

int Player::getX() const { return x; }

int Player::getY() const { return y; }

int Player::getHeadW() const { return head_rect.w; }

int Player::getHeadH() const { return head_rect.h; }
