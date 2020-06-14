#include "elf.h"

Elf::Elf(std::string path_body_tex, std::string path_head_tex,
         SDL_Renderer* ren, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  width = 25;
  height = 45;
  renderer = ren;
  body_rect = {0, 0, width, height};
  head_rect = {0, 0, 17, 16};
  animation_move = new Move(width, height, total_clips);
  body_texture.loadTexture(path_body_tex, renderer);
  head_texture.loadTexture(path_head_tex, renderer);
}

Elf::~Elf() {
  delete animation_move;
  body_texture.free();
  head_texture.free();
  renderer = nullptr;
}
/*
void Elf::render() {
  body_texture.render(renderer, &body_rect, x - width / 2, y - height / 2);
  head_texture.render(renderer, &head_rect, x - head_rect.w / 2,
                      y - height / 2 - head_rect.h / 2);
}*/
