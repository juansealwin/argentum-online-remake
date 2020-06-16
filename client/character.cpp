#include "character.h"

Character::~Character() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
}

void Character::move(move_t move_type) {
  body_rect = animation_move->getNextClip(move_type);
  updatePosition(move_type);
}

void Character::render(int x_rel, int y_rel) {
  body_texture.render(renderer, &body_rect, x - width / 2 - x_rel, y - height / 2 - y_rel);
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
