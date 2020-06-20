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
#define TILE_SIZE 32

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
  int clips_up_down;
  int clips_left_right;

 public:
  Move(int, int, int);
  ~Move();
  void set_offset_y(int);
  SDL_Rect get_next_clip(move_t);
  SDL_Rect next_clip_move_up();
  SDL_Rect next_clip_move_down();
  SDL_Rect next_clip_move_left();
  SDL_Rect next_clip_move_right();
  int set_total_clips(int);
};

#endif
