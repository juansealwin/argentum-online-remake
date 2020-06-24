#ifndef SPELL_H
#define SPELL_H

#include "drawable.h"

class Spell /*: public Drawable*/ {
 private:
  int life_time;

 public:
  Spell();
  ~Spell();
  //virtual void render(int, int) override;
};

#endif