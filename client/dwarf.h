#ifndef DWARF_H
#define DWARF_H

#include <string>
#define PATH_DWARF_BODY "enano.png"
#define PATH_DWARF_HEAD "cabeza_enano.png"
#include "move.h"
#include "character.h"
#include "texture.h"

class Dwarf : public Character {
 public:
  Dwarf(SDL_Renderer*, int, int);
  ~Dwarf();
};

#endif
