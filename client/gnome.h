#ifndef GNOME_H
#define GNOME_H

#include "texture.h"
#include "move.h"
#include <string>
#define GNOME_WIDTH 25
#define GNOME_HEIGHT 45
#define TOTAL_CLIPS 6
#define GNOME_HEAD_WIDTH 17
#define GNOME_HEAD_HEIGHT 17

class Gnome {
  private:
    Move animation_move;    

  public:
    Gnome();
    ~Gnome();
    SDL_Rect move(move_t);
    SDL_Rect getFaceProfile(move_t);
};

#endif