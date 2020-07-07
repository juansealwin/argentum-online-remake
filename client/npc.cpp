#include "npc.h"

Npc::Npc(entity_t id_npc, int new_x, int new_y) {
  x = new_x * TILE_SIZE;
  y = new_y * TILE_SIZE;
  set_character_features(id_npc);
  animation_move = Animation(width, height, type_character);
}

Npc::Npc(const Npc& other_npc) {
  /** Copiamos la parte de Drawable **/
  x = other_npc.x;
  y = other_npc.y;
  // Colocamos las dimensiones del personaje
  width = other_npc.width;
  height = other_npc.height;

  /** Copiamos la parte de Character **/
  type_character = other_npc.type_character;
  animation_move = other_npc.animation_move;
  body_rect = other_npc.body_rect;
  walk = other_npc.walk;
  spellbound = other_npc.spellbound;
}

Npc& Npc::operator=(const Npc& other_npc) {
  /** Copiamos la parte de Drawable **/
  x = other_npc.x;
  y = other_npc.y;
  // Colocamos las dimensiones del personaje
  width = other_npc.width;
  height = other_npc.height;

  /** Copiamos la parte de Character **/
  type_character = other_npc.type_character;
  animation_move = other_npc.animation_move;
  body_rect = other_npc.body_rect;
  walk = other_npc.walk;
  spellbound = other_npc.spellbound;
  return *this;
}

Npc::~Npc() {}

void Npc::sound_walk() {
  if ((rand() % 100) < 20) walk.play_sound(0);
}
