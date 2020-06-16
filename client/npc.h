#ifndef NPC_H
#define NPC_H

#include "character.h"
#include "drawable.h"
#include "paths.h"

class Npc : public Character {
 public:
  Npc(SDL_Renderer*, int, int, int);
  ~Npc();
  int setNpcDimensions(int);
};

#endif