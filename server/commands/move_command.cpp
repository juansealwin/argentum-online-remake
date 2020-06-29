#include "move_command.h"

#include <iostream>

#include "argentum_game.h"

MoveCommand::MoveCommand(const int entity_id, const int x_move, const int y_move)
    : entity_id(entity_id), x_move(x_move), y_move(y_move) {}

MoveCommand::~MoveCommand() {}

void MoveCommand::execute(ArgentumGame *game) {
  game->move_entity(entity_id, x_move, y_move);
}
