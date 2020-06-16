#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#define PATH_HUMAN_BODY "humano.png"
#define PATH_HUMAN_HEAD "cabeza_humano.png"
#include "move.h"
#include "character.h"

class Human : public Character {
 public:
  Human(SDL_Renderer*, int, int);
  ~Human();
};

#endif
