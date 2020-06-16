#include "gnome.h"

Gnome::Gnome(SDL_Renderer* ren, int new_x, int new_y) {
  half_screen_w = new_x;
  half_screen_h = new_y;
  x = new_x;
  y = new_y;
  width = 25;
  height = 45;
  renderer = ren;
  // El 10 de body_rect y del offset es debido a que el grafico es distinto
  body_rect = {0, 10, width, height};
  head_rect = {0, 0, 17, 17};
  animation_move = new Move(width, height, total_clips);
  animation_move->setOffsetY(10);
  body_texture.loadTexture(ID_GNOME, renderer);
  head_texture.loadTexture(ID_GNOME_HEAD, renderer);
}

Gnome::~Gnome() {
  delete animation_move;
  renderer = nullptr;
}
