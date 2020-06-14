#ifndef HUMAN_H
#define HUMAN_H

#include <string>

#include "move.h"
#include "player.h"

class Human : public Player {
 public:
  Human(std::string, std::string path_head_tex, SDL_Renderer*, int, int);
  ~Human();
  //virtual void render();
  // void update();
};

#endif
