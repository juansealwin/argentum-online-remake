#include "npc.h"

Npc::Npc(SDL_Renderer* ren, character_t id_npc, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  renderer = ren;
  set_character_dimensions(id_npc);
  animation_move = new Move(width, height, type_character);
  body_texture.load_texture(paths->get_path_texture(type_character), renderer);
}

Npc::~Npc() {
  delete animation_move;
  renderer = nullptr;
}
