#ifndef NPC_H
#define NPC_H

#include "character.h"
#include "drawable.h"
#include "paths.h"

class Npc : public Character {
 private:
  int id_npc;

 public:
  Npc(SDL_Renderer*, character_t, int, int);
  ~Npc();
  int set_npc_dimensions(character_t);
};

#endif