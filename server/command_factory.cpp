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
    case BANK_ITEM_COMMAND:
      return bank_item_command(dynamic_cast<BankItemCommandDTO*>(command_dto),
                               player_id);
    case UNBANK_ITEM_COMMAND:
      return unbank_item_command(
          dynamic_cast<UnbankItemCommandDTO*>(command_dto), player_id);
    case BANK_GOLD_COMMAND:
      return bank_gold_command(dynamic_cast<BankGoldCommandDTO*>(command_dto),
                               player_id);
    case UNBANK_GOLD_COMMAND:
      return unbank_gold_command(
          dynamic_cast<UnbankGoldCommandDTO*>(command_dto), player_id);
    case GET_BANKED_ITEMS_COMMAND:
      return new GetBankedItemsCommand(player_id);
    case BUY_ITEM_COMMAND:
      return buy_item_command(dynamic_cast<BuyItemCommandDTO*>(command_dto), player_id);
    case SELL_ITEM_COMMAND:
      return sell_item_command(dynamic_cast<SellItemCommandDTO*>(command_dto), player_id);
    case MEDITATE_COMMAND:
      return new MeditateCommand(player_id);
    case USE_ITEM_SPECIAL_COMMAND:
      return new UseItemSpecialCommand(player_id);
    case HEAL_COMMAND:
      return new HealCommand(player_id);
    case REVIVE_COMMAND:
      return new ReviveCommand(player_id);
    default:
      return nullptr;
  }
}

BuyItemCommand* CommandFactory::buy_item_command(BuyItemCommandDTO* command_dto, unsigned int player_id) {
  return new BuyItemCommand(player_id, command_dto->item);
}
SellItemCommand* CommandFactory::sell_item_command(SellItemCommandDTO* command_dto, unsigned int player_id) {
  return new SellItemCommand(player_id, command_dto->item);
}

BankItemCommand* CommandFactory::bank_item_command(BankItemCommandDTO* command_dto,
                                   unsigned int player_id) {
  return new BankItemCommand(player_id, command_dto->item);
}
UnbankItemCommand* CommandFactory::unbank_item_command(UnbankItemCommandDTO* command_dto,
                                       unsigned int player_id) {
  return new UnbankItemCommand(player_id, command_dto->item);
}
BankGoldCommand* CommandFactory::bank_gold_command(BankGoldCommandDTO* command_dto,
                                   unsigned int player_id) {
  return new BankGoldCommand(player_id, command_dto->ammount);
}
UnbankGoldCommand* CommandFactory::unbank_gold_command(UnbankGoldCommandDTO* command_dto,
                                       unsigned int player_id) {
  return new UnbankGoldCommand(player_id, command_dto->ammount);
}

PrivateMessageCommand* CommandFactory::pm_command(
    PrivateMessageDTO* command_dto, unsigned int player_id) {
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
    case (stop_move):
      break;
  }
  return new MoveCommand(player_id, x_move, y_move);
}