#include "elf.h"

Elf::Elf(SDL_Renderer* ren, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  width = 25;
  height = 45;
  renderer = ren;
  body_rect = {0, 0, width, height};
  head_rect = {0, 0, 17, 16};
  animation_move = new Move(width, height, total_clips);
  body_texture.loadTexture(PATH_ELF_BODY, renderer);
  head_texture.loadTexture(PATH_ELF_HEAD, renderer);
}

Elf::~Elf() {
  delete animation_move;
  renderer = nullptr;
}
