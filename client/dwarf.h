#ifndef DWARF_H
#define DWARF_H

#include <string>

#include "move.h"
#include "player.h"
#include "texture.h"

class Dwarf : public Player {
 public:
  Dwarf(std::string, std::string, SDL_Renderer*, int, int);
  ~Dwarf();
  //virtual void render();
};

#endif
