#include "command_factory.h"
#include <iostream>
Command* CommandFactory::create_command(CommandDTO* command_dto, unsigned int player_id) {
  int command_id = command_dto->get_id();
  switch (command_id) {
    case MOVE_COMMAND:
      return move_command(dynamic_cast<MoveCommandDTO*>(command_dto), player_id);
    case QUIT_COMMAND:
      return new QuitCommand(player_id);
    case ATTACK_COMMAND:
      return new AttackCommand(player_id);
    case PICK_UP_ITEM_COMMAND:
      return new PickUpDropCommand(player_id);
    default:
      return nullptr;
  }
}

Command* CommandFactory::move_command(MoveCommandDTO* command_dto, unsigned int player_id) {
  int x_move = 0;
  int y_move = 0;
  switch (command_dto->movement_type) {
    case (move_down):
      x_move = 1;
      break;
    case (move_left):
      y_move = -1;
      break;
    case (move_up):
      x_move = -1;
      break;
    case (move_right):
      y_move = 1;
      break;
  }
  return new MoveCommand(player_id, x_move, y_move);
}