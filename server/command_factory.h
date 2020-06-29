#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H
#include "command.h"
#include "command_dto.h"
#include "move_command.h"
#include "move_command_dto.h"
namespace CommandFactory {
Command* create_command(CommandDTO* command_dto);

MoveCommand* move_command(MoveCommandDTO* command_dto);
}  // namespace CommandFactory
#endif