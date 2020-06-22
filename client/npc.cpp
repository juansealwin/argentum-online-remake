#include "npc.h"

Npc::Npc(SDL_Renderer* ren, character_t id, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  set_npc_dimensions(id);
  renderer = ren;
  body_rect = {0, 0, width, height};
  animation_move = new Move(width, height, id_npc);
  body_texture.load_texture(paths->get_path_texture(id_npc), renderer);
}

Npc::~Npc() {
  delete animation_move;
  renderer = nullptr;
}

int Npc::set_npc_dimensions(character_t id) {
  switch (id) {
    case SPIDER:
      width = 53;
      height = 33;
      id_npc = ID_SPIDER;
      break;

    case SKELETON:
      width = 25;
      height = 52;
      id_npc = ID_SKELETON;
      break;

    case GOBLIN:
      width = 24;
      height = 33;
      id_npc = ID_GOBLIN;
      break;

    case ZOMBIE:
      width = 25;
      height = 47;
      id_npc = ID_ZOMBIE;
      break;

    case PRIEST:
      width = 25;
      height = 45;
      id_npc = ID_PRIEST;
      break;

    case MERCHANT:
      width = 23;
      height = 48;
      id_npc = ID_MERCHANT;
      break;

    case BANKER:
      width = 25;
      height = 33;
      id_npc = ID_BANKER;
      break;
  }
}