#include "animation.h"

Animation::Animation() {}

Animation::Animation(int char_width, int char_height, id_texture_t id_character)
    : character_width(char_width), character_height(char_height) {
  set_total_clips(id_character);
  current_clip[CLIP_DOWN] = 0;
  current_clip[CLIP_UP] = 0;
  current_clip[CLIP_LEFT] = 0;
  current_clip[CLIP_RIGHT] = 0;
}

Animation::Animation(int char_width, int char_height/*, size_t current_clip_down,
                     size_t current_clip_up, size_t current_clip_left,
                     size_t current_clip_right*/)
    : character_width(char_width), character_height(char_height) {
  // Todos los items equipables(menos cascos) tienen esta cantidad de frames
  clips_up_down = 5;
  clips_left_right = 4;
  current_clip[CLIP_DOWN] = 0;   // current_clip_down;
  current_clip[CLIP_UP] = 0;     // current_clip_up;
  current_clip[CLIP_LEFT] = 0;   // current_clip_left;
  current_clip[CLIP_RIGHT] = 0;  // current_clip_right;
}

Animation::Animation(const Animation& other_animation) {
  character_width = other_animation.character_width;
  character_height = other_animation.character_height;
  offset_y = other_animation.offset_y;
  current_clip = other_animation.current_clip;
  clips_up_down = other_animation.clips_up_down;
  clips_left_right = other_animation.clips_left_right;
}

Animation::~Animation() {}

SDL_Rect Animation::get_next_clip(move_t move_type) {
  switch (move_type) {
    case MOVE_DOWN:
      return next_clip_move_down();
      break;

    case MOVE_UP:
      return next_clip_move_up();
      break;

    case MOVE_LEFT:
      return next_clip_move_left();
      break;

    case MOVE_RIGHT:
      return next_clip_move_right();
      break;
  }
}

SDL_Rect Animation::get_next_clip(int lifetime, int max_lifetime) {
  int total_clips = clips_up_down * clips_up_down;
  int j = 0;
  int k = 0;

  for (size_t i = 1; i <= total_clips + 1; i++) {
    if (lifetime > (max_lifetime - FRAMES_PER_TEXTURE * i))
      break;
    else
      j++;
    if (j == clips_up_down) {
      j = 0;
      k++;
    }
  }
  return SDL_Rect{character_width * j, character_height * k, character_width,
                  character_height};
}

SDL_Rect Animation::next_clip_move_up() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_UP],
                        character_height + offset_y, character_width,
                        character_height};

  if (current_clip[CLIP_UP] == clips_up_down)
    current_clip[CLIP_UP] = 0;
  else
    current_clip[CLIP_UP] += 1;

  return next_clip;
}

SDL_Rect Animation::next_clip_move_down() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_DOWN], 0 + offset_y,
                        character_width, character_height};

  if (current_clip[CLIP_DOWN] == clips_up_down)
    current_clip[CLIP_DOWN] = 0;
  else
    current_clip[CLIP_DOWN] += 1;

  return next_clip;
}

SDL_Rect Animation::next_clip_move_left() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_LEFT],
                        character_height * 2 + offset_y, character_width,
                        character_height};

  if (current_clip[CLIP_LEFT] == clips_left_right)
    current_clip[CLIP_LEFT] = 0;
  else
    current_clip[CLIP_LEFT] += 1;

  return next_clip;
}

SDL_Rect Animation::next_clip_move_right() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_RIGHT],
                        character_height * 3 + offset_y, character_width,
                        character_height};

  if (current_clip[CLIP_RIGHT] == clips_left_right)
    current_clip[CLIP_RIGHT] = 0;
  else
    current_clip[CLIP_RIGHT] += 1;

  return next_clip;
}

int Animation::set_total_clips(id_texture_t id) {
  // Seteamos el total de clips -1, ya que el 0 lo cuenta
  switch (id) {
    case ID_CORPSE:
      clips_up_down = 2;
      clips_left_right = 2;
      break;

    case ID_HUMAN:
    case ID_ELF:
    case ID_DWARF:
    case ID_GNOME:
      clips_up_down = 5;
      clips_left_right = 4;
      break;

    case ID_SPIDER:
      clips_up_down = 3;
      clips_left_right = 3;
      break;

    case ID_SKELETON:
      clips_up_down = 5;
      clips_left_right = 4;
      break;

    case ID_GOBLIN:
      clips_up_down = 7;
      clips_left_right = 7;
      break;

    case ID_ZOMBIE:
      clips_up_down = 5;
      clips_left_right = 4;
      break;

    case ID_PRIEST:
      clips_up_down = 6;
      clips_left_right = 6;
      break;

    case ID_MERCHANT:
      clips_up_down = 2;
      clips_left_right = 2;
      break;

    case ID_BANKER:
      clips_up_down = 5;
      clips_left_right = 5;
      break;

    case ID_MAGIC_ARROW:
      // Columnas de clips
      clips_up_down = 8;
      // Filas de clips
      clips_left_right = 1;
      break;

    case ID_HEAL:
      // Columnas de clips
      clips_up_down = 5;
      // Filas de clips
      clips_left_right = 2;
      break;
  }
}

void Animation::set_offset_y(int offset) { offset_y = offset; }
