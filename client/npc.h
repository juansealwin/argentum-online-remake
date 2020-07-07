#ifndef NPC_H
#define NPC_H

#include "character.h"

class Npc : public Character {
 public:
  Npc(entity_t, int, int);
  Npc(const Npc&);
  ~Npc();
  Npc& operator=(const Npc&);
  virtual void sound_walk() override;
};

#endif