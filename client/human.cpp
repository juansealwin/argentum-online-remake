#include "human.h"

Human::Human() {}

Human::~Human() {}

SDL_Rect Human::moveUp() {
  return animation_up.getNextClip();
}