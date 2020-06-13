#ifndef MOVE_H
#define MOVE_H

#include <map>
#include <vector>

#include "texture.h"
#define CLIP_DOWN 'D'
#define CLIP_UP 'U'
#define CLIP_LEFT 'L'
#define CLIP_RIGHT 'R'
#define CHARACTER_HEIGHT 45
#define CHARACTER_WIDTH 25

typedef enum {
    MOVE_DOWN = 0,
    MOVE_UP = 3,
    MOVE_LEFT = 2,
    MOVE_RIGHT = 1
} move_t;

class Move {
   private:
    int character_width;
    int character_height;
    int offset_y = 0;
    std::map<char, size_t> current_clip;
    int total_clips;

   public:
    Move(int, int, int);
    ~Move();

    void setOffsetY(int);

    SDL_Rect getNextClip(move_t);

    SDL_Rect nextClipMoveUp();

    SDL_Rect nextClipMoveDown();

    SDL_Rect nextClipMoveLeft();

    SDL_Rect nextClipMoveRight();
};

#endif