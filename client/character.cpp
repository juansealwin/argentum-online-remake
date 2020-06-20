#include "character.h"

Character::~Character() {
  delete animation_move;
  renderer = nullptr;
  body_texture.free();
}

void Character::move(move_t move_type) {
  body_rect = animation_move->get_next_clip(move_type);
}

void Character::render(int x_rel, int y_rel) {
  body_texture.render(renderer, &body_rect, x - width / 2 - x_rel,
                      y - height / 2 - y_rel);
}

void Character::update_position(int new_x, int new_y) {
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

int Character::get_width() const { return width; }

int Character::get_height() const { return height; }

int Character::get_x() const { return x; }

int Character::get_y() const { return y; }

int Character::get_id() const { return id; }