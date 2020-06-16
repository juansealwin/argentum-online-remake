#include "move.h"

Move::Move(int char_width, int char_height, int id_character)
    : character_width(char_width), character_height(char_height) {
  setTotalClips(id_character);
  current_clip[CLIP_DOWN] = 0;
  current_clip[CLIP_UP] = 0;
  current_clip[CLIP_LEFT] = 0;
  current_clip[CLIP_RIGHT] = 0;
}

Move::~Move() {}

SDL_Rect Move::getNextClip(move_t move_type) {
  switch (move_type) {
    case MOVE_DOWN:
      return nextClipMoveDown();
      break;

    case MOVE_UP:
      return nextClipMoveUp();
      break;

    case MOVE_LEFT:
      return nextClipMoveLeft();
      break;

    case MOVE_RIGHT:
      return nextClipMoveRight();
      break;
  }
}

SDL_Rect Move::nextClipMoveUp() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_UP],
                        character_height + offset_y, character_width,
                        character_height};

  if (current_clip[CLIP_UP] == clips_up_down)
    current_clip[CLIP_UP] = 0;
  else
    current_clip[CLIP_UP] += 1;

  return next_clip;
}

SDL_Rect Move::nextClipMoveDown() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_DOWN], 0 + offset_y,
                        character_width, character_height};

  if (current_clip[CLIP_DOWN] == clips_up_down)
    current_clip[CLIP_DOWN] = 0;
  else
    current_clip[CLIP_DOWN] += 1;

  return next_clip;
}

SDL_Rect Move::nextClipMoveLeft() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_LEFT],
                        character_height * 2 + offset_y, character_width,
                        character_height};

  if (current_clip[CLIP_LEFT] == clips_left_right)
    current_clip[CLIP_LEFT] = 0;
  else
    current_clip[CLIP_LEFT] += 1;

  return next_clip;
}

SDL_Rect Move::nextClipMoveRight() {
  SDL_Rect next_clip = {character_width * current_clip[CLIP_RIGHT],
                        character_height * 3 + offset_y, character_width,
                        character_height};

  if (current_clip[CLIP_RIGHT] == clips_left_right)
    current_clip[CLIP_RIGHT] = 0;
  else
    current_clip[CLIP_RIGHT] += 1;

  return next_clip;
}

int Move::setTotalClips(int id) {
  //Seteamos el total de clips -1, ya que el 0 lo cuenta
  switch (id) {
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
      clips_up_down = 0;
      clips_left_right = 0;
      break;

    case ID_BANKER:
      clips_up_down = 5;
      clips_left_right = 5;
      break;
  }
}

void Move::setOffsetY(int offset) { offset_y = offset; }
