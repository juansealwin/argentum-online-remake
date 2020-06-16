#include "npc.h"

Npc::Npc(SDL_Renderer* ren, int id, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  setNpcDimensions(id);
  renderer = ren;
  body_rect = {0, 0, width, height};
  animation_move = new Move(width, height, id);
  body_texture.loadTexture(id, renderer);
}

Npc::~Npc() {
  delete animation_move;
  renderer = nullptr;
}

int Npc::setNpcDimensions(int id_npc) {
  switch (id_npc) {
    case ID_SPIDER:
      width = 53;
      height = 33;
      break;

    case ID_SKELETON:
      width = 25;
      height = 52;
      break;

    case ID_GOBLIN:
      width = 24;
      height = 33;
      break;

    case ID_ZOMBIE:
      width = 25;
      height = 47;
      break;

    case ID_PRIEST:
      width = 25;
      height = 45;
      break;

    case ID_MERCHANT:
      width = 23;
      height = 48;
      break;

    case ID_BANKER:
      width = 25;
      height = 33;
      break;
  }
}