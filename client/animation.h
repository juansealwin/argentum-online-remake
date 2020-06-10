#ifndef ANIMATION_H
#define ANIMATION_H

#include "texture.h"
#include <vector>

#define CHARACTER HEIGHT 45
#define CHARACTER_WIDTH 25

typedef enum {WALK_DOWN, WALK_UP, WALK_LEFT, WALK_RIGHT} movement_t;

class Animation {
   private:
    Texture* current_texture;
    std::vector<SDL_Rect> sprite;

   public:
    Animation();
    ~Animation();
    void loadTexture(Texture*);
};

#endif