#ifndef ANIMATION_H
#define ANIMATION_H

#include "texture.h"

class Animation {
   private:
    Texture* current_texture;

   public:
    Animation();
    ~Animation();
    void loadTexture(Texture*);
};

#endif