#include "move.h"

Move::Move(int char_width, int char_height, int tot_clips)
    : character_width(char_width),
      character_height(char_height),
      total_clips(tot_clips) {
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

    if (current_clip[CLIP_UP] == total_clips - 1)
        current_clip[CLIP_UP] = 0;
    else
        current_clip[CLIP_UP] += 1;

    return next_clip;
}

SDL_Rect Move::nextClipMoveDown() {
    SDL_Rect next_clip = {character_width * current_clip[CLIP_DOWN],
                          0 + offset_y, character_width, character_height};

    if (current_clip[CLIP_DOWN] == total_clips - 1)
        current_clip[CLIP_DOWN] = 0;
    else
        current_clip[CLIP_DOWN] += 1;

    return next_clip;
}

SDL_Rect Move::nextClipMoveLeft() {
    SDL_Rect next_clip = {character_width * current_clip[CLIP_LEFT],
                          character_height * 2 + offset_y, character_width,
                          character_height};

    if (current_clip[CLIP_LEFT] == total_clips - 2)
        current_clip[CLIP_LEFT] = 0;
    else
        current_clip[CLIP_LEFT] += 1;

    return next_clip;
}

SDL_Rect Move::nextClipMoveRight() {
    SDL_Rect next_clip = {character_width * current_clip[CLIP_RIGHT],
                          character_height * 3 + offset_y, character_width,
                          character_height};

    if (current_clip[CLIP_RIGHT] == total_clips - 2)
        current_clip[CLIP_RIGHT] = 0;
    else
        current_clip[CLIP_RIGHT] += 1;

    return next_clip;
}

void Move::setOffsetY(int offset) { offset_y = offset; }