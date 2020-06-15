#include "move_command.h"

#include <iostream>

#include "argentum_game.h"
MoveCommand::MoveCommand(int entity_id, int next_x, int next_y)
    : entity_id(entity_id), next_x(next_x), next_y(next_y) {}

MoveCommand::~MoveCommand() {}

void MoveCommand::execute(ArgentumGame *game) {
  game->move_entity(entity_id, next_x, next_y);
}
