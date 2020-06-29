#include "command_factory.h"
#include <iostream>
Command* CommandFactory::create_command(CommandDTO* command_dto) {
  int command_id = command_dto->getId();
  switch (command_id) {
    case MOVE_COMMAND:
      return move_command(dynamic_cast<MoveCommandDTO*>(command_dto));
  }
}

MoveCommand* CommandFactory::move_command(MoveCommandDTO* command_dto) {
  int x_move = 0;
  int y_move = 0;
  switch (command_dto->movement_type) {
    case (move_down):
      x_move = -1;
      break;
    case (move_left):
      y_move = -1;
      break;
    case (move_up):
      x_move = 1;
      break;
    case (move_right):
      y_move = 1;
      break;
  std::cout << "x_move: " << x_move << " y_move " << y_move << std::endl;
  }
  return new MoveCommand(command_dto->player_id, x_move, y_move);
}