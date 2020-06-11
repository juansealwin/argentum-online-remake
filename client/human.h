#ifndef HUMAN_H
#define HUMAN_H


#include "texture.h"
#include "move.h"
#include <string>
#define HUMAN_WIDTH 25
#define HUMAN_HEIGHT 45
#define TOTAL_CLIPS 6

class Human {
  private:
    //std::string image_path;
    Move animation_move;
    

  public:
    Human();
    ~Human();
    SDL_Rect move(move_t);
};

#endif