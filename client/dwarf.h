#ifndef DWARF_H
#define DWARF_H

#include "texture.h"
#include "move.h"
#include <string>
#define DWARF_WIDTH 25
#define DWARF_HEIGHT 45
#define TOTAL_CLIPS 6
#define DWARF_HEAD_WIDTH 17
#define DWARF_HEAD_HEIGHT 17

class Dwarf {
  private:
    Move animation_move;    

  public:
    Dwarf();
    ~Dwarf();
    SDL_Rect move(move_t);
    SDL_Rect getFaceProfile(move_t);
};

#endif