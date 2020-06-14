#include "gnome.h"

Gnome::Gnome(std::string path_body_tex, std::string path_head_tex,
             SDL_Renderer* ren, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  width = 25;
  height = 45;
  renderer = ren;
  body_rect = {0, 0, width, height};
  head_rect = {0, 0, 17, 17};
  animation_move = new Move(width, height, total_clips);
  animation_move->setOffsetY(10);
  body_texture.loadTexture(path_body_tex, renderer);
  head_texture.loadTexture(path_head_tex, renderer);
}

Gnome::~Gnome() {
  delete animation_move;
  body_texture.free();
  head_texture.free();
  renderer = nullptr;
}

