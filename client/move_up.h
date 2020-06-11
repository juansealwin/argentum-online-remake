#ifndef MOVE_UP_H
#define MOVE_UP_H

#include "texture.h"
#include <vector>

#define CHARACTER_HEIGHT 45
#define CHARACTER_WIDTH 25

//typedef enum {WALK_DOWN, WALK_UP, WALK_LEFT, WALK_RIGHT} movement_t;

class MoveUp {
   private:
    int character_width = 25;
    int character_height = 45;
    int current_clip = 1;
    int total_clips = 6;
    

   public:
    MoveUp();
    ~MoveUp();
    //void chargeSprite();
    SDL_Rect getNextClip();
};

#endif