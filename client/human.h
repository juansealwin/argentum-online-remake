#ifndef HUMAN_H
#define HUMAN_H


#include "texture.h"
#include "move_up.h"
#include <string>

class Human {
  private:
    //std::string image_path;
    MoveUp animation_up;

  public:
    Human();
    ~Human();
    SDL_Rect moveUp();
};

#endif