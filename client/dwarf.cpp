#include "dwarf.h"

Dwarf::Dwarf(std::string path_body_tex, std::string path_head_tex,
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

Dwarf::~Dwarf() {
  delete animation_move;
  body_texture.free();
  head_texture.free();
  renderer = nullptr;
}
/*
void Dwarf::render() {
  body_texture.render(renderer, &body_rect, x - width / 2, y - height / 2);
  head_texture.render(renderer, &head_rect, x - head_rect.w / 2,
                      y - height / 2 - head_rect.h / 2);
}*/
