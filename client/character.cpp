#include "character.h"

Character::~Character() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
}

void Character::move(move_t move_type) {
  body_rect = animation_move->getNextClip(move_type);
}

void Character::render(int x_rel, int y_rel) {
  body_texture.render(renderer, &body_rect, x - width / 2 - x_rel,
                      y - height / 2 - y_rel);
}

void Character::updatePosition(int new_x, int new_y) {
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

int Character::getWidth() const { return width; }

int Character::getHeight() const { return height; }

int Character::getX() const { return x; }

int Character::getY() const { return y; }

int Character::getId() const { return id; }