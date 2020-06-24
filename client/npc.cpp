#include "npc.h"

Npc::Npc(character_t id_npc, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  set_character_dimensions(id_npc);
  animation_move = Move(width, height, type_character);
}

Npc::Npc(const Npc& other_npc) {
  x = other_npc.x;
  y = other_npc.y;
  type_character = other_npc.type_character;
  // Colocamos las dimensiones del personaje
  width = other_npc.width;
  height = other_npc.height;
  body_rect = other_npc.body_rect;
  animation_move = other_npc.animation_move;
}

Npc& Npc::operator=(const Npc& other_npc) {
  x = other_npc.x;
  y = other_npc.y;
  type_character = other_npc.type_character;
  // Colocamos las dimensiones del personaje
  width = other_npc.width;
  height = other_npc.height;
  body_rect = other_npc.body_rect;
  animation_move = other_npc.animation_move;
}

Npc::~Npc() {}
