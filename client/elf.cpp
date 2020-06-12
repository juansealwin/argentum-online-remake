#include "elf.h"

Elf::Elf() : animation_move(ELF_WIDTH, ELF_HEIGHT, TOTAL_CLIPS) {}

Elf::~Elf() {}

SDL_Rect Elf::move(move_t move_type) {
    return animation_move.getNextClip(move_type);
}

SDL_Rect Elf::getFaceProfile(move_t move_type) {
    SDL_Rect face_profile = {move_type * ELF_HEAD_WIDTH, 0, ELF_HEAD_WIDTH,
                             ELF_HEAD_HEIGHT};
    return face_profile;
}