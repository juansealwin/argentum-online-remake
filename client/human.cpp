#include "human.h"

Human::Human(SDL_Renderer* ren, int id_char, int new_x, int new_y) {
  id = id_char;
  half_screen_w = new_x;
  half_screen_h = new_y;
  x = new_x;
  y = new_y;
  width = 25;
  height = 45;
  renderer = ren;
  body_rect = {0, 0, width, height};
  head_rect = {0, 0, 17, 16};
  animation_move = new Move(width, height, ID_HUMAN);
  body_texture.loadTexture(ID_HUMAN, renderer);
  head_texture.loadTexture(ID_HUMAN_HEAD, renderer);
}

Human::~Human() {
  delete animation_move;
  renderer = nullptr;
}
