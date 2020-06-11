#include "human.h"

Human::Human() : animation_move(HUMAN_WIDTH, HUMAN_HEIGHT, TOTAL_CLIPS) {}

Human::~Human() {}

SDL_Rect Human::move(move_t move_type) {
    return animation_move.getNextClip(move_type);
}