#include "argentum_game.h"

#include <iostream>

ArgentumGame::ArgentumGame(const unsigned int room_number)
    : room(room_number) {}

ArgentumGame::~ArgentumGame() {}

const unsigned int ArgentumGame::get_room() { return room; }
