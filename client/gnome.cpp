#include "gnome.h"

Gnome::Gnome() : animation_move(GNOME_WIDTH, GNOME_HEIGHT, TOTAL_CLIPS) {}

Gnome::~Gnome() {}

SDL_Rect Gnome::move(move_t move_type) {
    return animation_move.getNextClip(move_type);
}

SDL_Rect Gnome::getFaceProfile(move_t move_type) {
    SDL_Rect face_profile = {move_type * GNOME_HEAD_WIDTH, 0, GNOME_HEAD_WIDTH,
                             GNOME_HEAD_HEIGHT};
    return face_profile;
}