#include "character.h"

Character::~Character() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
  head_texture.free();
}

void Character::move(move_t move_type) {
  body_rect = animation_move->getNextClip(move_type);
  updateFaceProfile(move_type);
  updatePosition(move_type);
}

void Character::updateFaceProfile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

void Character::render() {
  body_texture.render(renderer, &body_rect, half_screen_w - width / 2,
                      half_screen_h - height / 2);
  head_texture.render(renderer, &head_rect, half_screen_w - head_rect.w / 2,
                      half_screen_h - height / 2 - head_rect.h / 2);
}

void Character::updatePosition(move_t move_type) {
  switch (move_type) {
    case MOVE_DOWN:
      y += TILE_SIZE;
      break;

    case MOVE_UP:
      y -= TILE_SIZE;
      break;

    case MOVE_LEFT:
      x -= TILE_SIZE;
      break;
    
    case MOVE_RIGHT:
      x += TILE_SIZE;
      break;
  }
}

int Character::getWidth() const { return width; }

int Character::getHeight() const { return height; }

int Character::getX() const { return x; }

int Character::getY() const { return y; }

int Character::getHeadW() const { return head_rect.w; }

int Character::getHeadH() const { return head_rect.h; }
