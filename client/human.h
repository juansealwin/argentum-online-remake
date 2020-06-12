#ifndef HUMAN_H
#define HUMAN_H


#include "texture.h"
#include "move.h"
#include <string>
#define HUMAN_WIDTH 25
#define HUMAN_HEIGHT 45
#define TOTAL_CLIPS 6
#define HUMAN_HEAD_WIDTH 17
#define HUMAN_HEAD_HEIGHT 16

class Human {
  private:
    Move animation_move;
    

  public:
    Human();
    ~Human();
    SDL_Rect move(move_t);
    SDL_Rect getFaceProfile(move_t);
};

#endif