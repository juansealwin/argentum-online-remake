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
namespace CommandFactory {
Command* create_command(CommandDTO* command_dto, unsigned int player_id);

MoveCommand* move_command(MoveCommandDTO* command_dto, unsigned int player_id);
UseItemCommand* use_item_command(UseItemCommandDTO* command_dto, unsigned int player_id);
DropItemCommand* drop_item_command(DropItemCommandDTO* command_dto, unsigned int player_id);
PrivateMessageCommand* pm_command(PrivateMessageDTO* command_dto, unsigned int player_id);

}  // namespace CommandFactory


#endif