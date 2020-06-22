#include "gnome.h"

Gnome::Gnome(SDL_Renderer* ren, int id_char, int new_x, int new_y) {
  id = id_char;
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
  animation_move = new Move(width, height, ID_GNOME);
  animation_move->set_offset_y(10);
  body_texture.load_texture(ID_GNOME, renderer);
  head_texture.load_texture(ID_GNOME_HEAD, renderer);
}

Gnome::~Gnome() {
  delete animation_move;
  renderer = nullptr;
}
