#include "move_command.h"

#include <iostream>

#include "argentum_game.h"

MoveCommand::MoveCommand(const int uid, const int x_move, const int y_move)
    : Command(uid), x_move(x_move), y_move(y_move) {}

MoveCommand::~MoveCommand() {}

void MoveCommand::execute(ArgentumGame *game) {
  game->move_entity(uid, x_move, y_move);
}
