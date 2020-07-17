#include "npc.h"

Npc::Npc(entity_t id_npc, int new_x, int new_y, move_t orient) {
  x = new_x;
  y = new_y;
  orientation = orient;
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
  orientation = other_npc.orientation;
  animation_move = other_npc.animation_move;
  body_rect = other_npc.body_rect;
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
  orientation = other_npc.orientation;
  animation_move = other_npc.animation_move;
  body_rect = other_npc.body_rect;
  spellbound = other_npc.spellbound;
  return *this;
}

Npc::~Npc() {}

sound_t Npc::sound_walk() {
  if ((rand() % 100) < 20) return walk;
}
