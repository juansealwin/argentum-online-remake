#include "npc.h"

Npc::Npc(SDL_Renderer* ren, character_t id, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  set_npc_dimensions(id);
  renderer = ren;
  body_rect = {0, 0, width, height};
  body_texture.load_texture(id, renderer);
}

Npc::~Npc() {
  delete animation_move;
  renderer = nullptr;
}

int Npc::set_npc_dimensions(character_t id_npc) {
  // cambiar esto
  int id_move;

  switch (id_npc) {
    case SPIDER:
      width = 53;
      height = 33;
      id_move = ID_SPIDER;
      break;

    case SKELETON:
      width = 25;
      height = 52;
      id_move = ID_SKELETON;
      break;

    case GOBLIN:
      width = 24;
      height = 33;
      id_move = ID_GOBLIN;

      break;

    case ZOMBIE:
      width = 25;
      height = 47;
      id_move = ID_ZOMBIE;
      break;

    case PRIEST:
      width = 25;
      height = 45;
      id_move = ID_PRIEST;
      break;

    case MERCHANT:
      width = 23;
      height = 48;
      id_move = ID_MERCHANT;
      break;

    case BANKER:
      width = 25;
      height = 33;
      id_move = ID_BANKER;
      break;
  }
  animation_move = new Move(width, height, id_move);
}