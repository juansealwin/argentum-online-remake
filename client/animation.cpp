#include "animation.h"

Animation::Animation(){
  current_texture = NULL;
}

Animation::~Animation(){
  current_texture = NULL;
}

void Animation::loadTexture(Texture* new_texture){
  current_texture = new_texture;
}