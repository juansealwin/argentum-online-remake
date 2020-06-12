#ifndef ELF_H
#define ELF_H

#include "texture.h"
#include "move.h"
#include <string>
#define ELF_WIDTH 25
#define ELF_HEIGHT 45
#define TOTAL_CLIPS 6
#define ELF_HEAD_WIDTH 17
#define ELF_HEAD_HEIGHT 17

class Elf {
  private:
    //std::string image_path;
    Move animation_move;
    

  public:
    Elf();
    ~Elf();
    SDL_Rect move(move_t);
    SDL_Rect getFaceProfile(move_t);
};

#endif
