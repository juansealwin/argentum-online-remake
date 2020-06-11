#include "move_up.h"

MoveUp::MoveUp() {}

MoveUp::~MoveUp() {}


SDL_Rect MoveUp::getNextClip() { 
  SDL_Rect next_clip = {character_width*current_clip, 
                        character_height, 
                        character_width, 
                        character_height};
  
  
  if(current_clip == total_clips-1)
    current_clip = 0;
  else 
    current_clip++;

  return next_clip;
}
