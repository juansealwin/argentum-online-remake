#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H
#include "command.h"
#include "command_dto.h"
#include "move_command.h"
#include "move_command_dto.h"
#include "quit_command.h"
#include "attack_command.h"
#include "pick_up_drop_command.h"
#include "use_item_command_dto.h"
#include "use_item_command.h"
#include "drop_item_command_dto.h"
#include "drop_item_command.h"
#include "private_message_dto.h"
#include "private_message_command.h"
#include "bank_item_command_dto.h"
#include "bank_item_command.h"
#include "bank_gold_command_dto.h"
#include "bank_gold_command.h"
#include "unbank_gold_command_dto.h"
#include "unbank_gold_command.h"
#include "unbank_item_command_dto.h"
#include "unbank_item_command.h"
#include "get_banked_items_command_dto.h"
#include "get_banked_items_command.h"
#include "sell_item_command_dto.h"
#include "sell_item_command.h"
#include "buy_item_command_dto.h"
#include "buy_item_command.h"

namespace CommandFactory {
Command* create_command(CommandDTO* command_dto, unsigned int player_id);

MoveCommand* move_command(MoveCommandDTO* command_dto, unsigned int player_id);
UseItemCommand* use_item_command(UseItemCommandDTO* command_dto, unsigned int player_id);
DropItemCommand* drop_item_command(DropItemCommandDTO* command_dto, unsigned int player_id);
PrivateMessageCommand* pm_command(PrivateMessageDTO* command_dto, unsigned int player_id);
BankItemCommand* bank_item_command(BankItemCommandDTO* command_dto, unsigned int player_id);
UnbankItemCommand* unbank_item_command(UnbankItemCommandDTO* command_dto, unsigned int player_id);
BankGoldCommand* bank_gold_command(BankGoldCommandDTO* command_dto, unsigned int player_id);
UnbankGoldCommand* unbank_gold_command(UnbankGoldCommandDTO* command_dto, unsigned int player_id);
BuyItemCommand* buy_item_command(BuyItemCommandDTO* command_dto, unsigned int player_id);
SellItemCommand* sell_item_command(SellItemCommandDTO* command_dto, unsigned int player_id);
}  // namespace CommandFactory


#endif