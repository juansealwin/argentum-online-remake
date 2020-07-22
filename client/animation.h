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

class Animation {
 private:
  int character_width;
  int character_height;
  std::map<char, int> current_clip;
  int clips_up_down;
  int clips_left_right;

 public:
  Animation();
  // Constructor para animaciones de personajes
  Animation(int, int, id_texture_t);
  // Construsctor para animaciones de items
  Animation(int, int);
  ~Animation();
  // Para personajes
  SDL_Rect get_next_clip(move_t);
  // Para estados
  SDL_Rect get_next_clip();
  // Para estados de duración finita
  SDL_Rect get_next_clip(int, int);
  SDL_Rect next_clip_move_up();
  SDL_Rect next_clip_move_down();
  SDL_Rect next_clip_move_left();
  SDL_Rect next_clip_move_right();
  void set_total_clips(id_texture_t);
};

#endif
