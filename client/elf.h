#ifndef ELF_H
#define ELF_H

#include <string>
#define PATH_ELF_BODY "elfo.png"
#define PATH_ELF_HEAD "cabeza_elfo.png"
#include "move.h"
#include "player.h"
#include "texture.h"

class Elf : public Player {
 public:
  Elf(SDL_Renderer*, int, int);
  ~Elf();
};

#endif
