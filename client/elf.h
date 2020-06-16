#ifndef ELF_H
#define ELF_H

#include <string>
#define PATH_ELF_BODY "elfo.png"
#define PATH_ELF_HEAD "cabeza_elfo.png"
#include "move.h"
#include "playable_character.h"
#include "texture.h"

class Elf : public PlayableCharacter {
 public:
  Elf(SDL_Renderer*, int, int);
  ~Elf();
};

#endif
