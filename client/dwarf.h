#ifndef DWARF_H
#define DWARF_H

#include <string>
#define PATH_DWARF_BODY "enano.png"
#define PATH_DWARF_HEAD "cabeza_enano.png"
#include "move.h"
#include "playable_character.h"
#include "texture.h"

class Dwarf : public PlayableCharacter {
 public:
  Dwarf(SDL_Renderer*,int, int, int);
  ~Dwarf();
};

#endif
