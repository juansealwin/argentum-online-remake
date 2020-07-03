#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H
#include "command.h"
#include "command_dto.h"
#include "move_command.h"
#include "move_command_dto.h"
#include "quit_command.h"
namespace CommandFactory {
Command* create_command(CommandDTO* command_dto, unsigned int player_id);

MoveCommand* move_command(MoveCommandDTO* command_dto, unsigned int player_id);
}  // namespace CommandFactory
#endif