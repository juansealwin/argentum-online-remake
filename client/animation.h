#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>
#include <vector>

#include "texture.h"
#include "types.h"
#define CLIP_DOWN 'D'
#define CLIP_UP 'U'
#define CLIP_LEFT 'L'
#define CLIP_RIGHT 'R'
#define TILE_SIZE 32

class Animation {
 private:
  int character_width;
  int character_height;
  int offset_y = 0;
  std::map<char, size_t> current_clip;
  int clips_up_down;
  int clips_left_right;

 public:
  Animation();
  Animation(int, int, id_texture_t);
  Animation(const Animation&);
  ~Animation();
  void set_offset_y(int);
  SDL_Rect get_next_clip(move_t);
  SDL_Rect next_clip_move_up();
  SDL_Rect next_clip_move_down();
  SDL_Rect next_clip_move_left();
  SDL_Rect next_clip_move_right();
  int set_total_clips(id_texture_t);
};

#endif
