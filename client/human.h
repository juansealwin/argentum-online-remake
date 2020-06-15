#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#define PATH_HUMAN_BODY "humano.png"
#define PATH_HUMAN_HEAD "cabeza_humano.png"
#include "move.h"
#include "player.h"

class Human : public Player {
 public:
  Human(SDL_Renderer*, int, int);
  ~Human();
};

#endif
