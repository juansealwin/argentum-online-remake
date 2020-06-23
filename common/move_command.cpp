#include "move_command.h"

#include <iostream>

#include "argentum_game.h"
MoveCommand::MoveCommand(const int entity_id, const int next_x, const int next_y)
    : entity_id(entity_id), next_x(next_x), next_y(next_y) {}

MoveCommand::~MoveCommand() {}

void MoveCommand::execute(ArgentumGame *game) {
  game->move_entity(entity_id, next_x, next_y);
}
