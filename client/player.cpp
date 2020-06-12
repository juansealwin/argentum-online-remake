#include "player.h"

Player::Player() {}

Player::~Player() { delete animation_move; }

SDL_Rect Player::move(move_t move_type) {
    return animation_move->getNextClip(move_type);
}

SDL_Rect Player::getFaceProfile(move_t move_type) {
    SDL_Rect face_profile = {move_type * head_w, 0, head_w, head_h};
    return face_profile;
}

int Player::getBodyW() { return body_w; }

int Player::getBodyH() { return body_h; }

int Player::getHeadW() { return head_w; }

int Player::getHeadH() { return head_h; }