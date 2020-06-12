#include "dwarf.h"

Dwarf::Dwarf() : animation_move(DWARF_WIDTH, DWARF_HEIGHT, TOTAL_CLIPS) {}

Dwarf::~Dwarf() {}

SDL_Rect Dwarf::move(move_t move_type) {
    return animation_move.getNextClip(move_type);
}

SDL_Rect Dwarf::getFaceProfile(move_t move_type) {
    SDL_Rect face_profile = {move_type * DWARF_HEAD_WIDTH, 0, DWARF_HEAD_WIDTH,
                             DWARF_HEAD_HEIGHT};
    return face_profile;
}