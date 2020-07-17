#ifndef NPC_H
#define NPC_H

#include "character.h"

class Npc : public Character {
 public:
  Npc(entity_t, int, int, move_t);
  Npc(const Npc&);
  ~Npc();
  Npc& operator=(const Npc&);
  virtual sound_t sound_walk() override;
};

#endif