#ifndef ELF_H
#define ELF_H

#include <string>

#include "move.h"
#include "player.h"
#include "texture.h"

class Elf : public Player {
 public:
  Elf(std::string , std::string ,
         SDL_Renderer* , int , int );
  ~Elf();
  //virtual void render();
};

#endif
