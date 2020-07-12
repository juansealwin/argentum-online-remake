#include "command_factory.h"

#include <iostream>
Command* CommandFactory::create_command(CommandDTO* command_dto,
                                        unsigned int player_id) {
  int command_id = command_dto->get_id();
  switch (command_id) {
    case MOVE_COMMAND:
      return move_command(dynamic_cast<MoveCommandDTO*>(command_dto),
                          player_id);
    case QUIT_COMMAND:
      return new QuitCommand(player_id);
    case ATTACK_COMMAND:
      return new AttackCommand(player_id);
    case PICK_UP_ITEM_COMMAND:
      return new PickUpDropCommand(player_id);
    case USE_ITEM_COMMAND:
      return use_item_command(dynamic_cast<UseItemCommandDTO*>(command_dto),
                              player_id);
    case DROP_ITEM_COMMAND:
      return drop_item_command(dynamic_cast<DropItemCommandDTO*>(command_dto),
                               player_id);
    case PRIVATE_MESSAGE_COMMAND:
      return pm_command(dynamic_cast<PrivateMessageDTO*>(command_dto),
                        player_id);
    default:
      return nullptr;
  }
}

PrivateMessageCommand* CommandFactory::pm_command(PrivateMessageDTO* command_dto,
                                  unsigned int player_id) {
  return new PrivateMessageCommand(player_id, command_dto->get_dst(),
                                   command_dto->get_msg());
}

DropItemCommand* CommandFactory::drop_item_command(
    DropItemCommandDTO* command_dto, unsigned int player_id) {
  return new DropItemCommand(player_id, command_dto->item_id);
}

UseItemCommand* CommandFactory::use_item_command(UseItemCommandDTO* command_dto,
                                                 unsigned int player_id) {
  return new UseItemCommand(player_id, command_dto->item,
                            command_dto->item_slot, command_dto->equipped);
}

MoveCommand* CommandFactory::move_command(MoveCommandDTO* command_dto,
                                          unsigned int player_id) {
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