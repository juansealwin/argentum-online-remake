#include "drop_item_command.h"

DropItemCommand::DropItemCommand(const unsigned int uid, const int item)
    : Command(uid), item(item) {}

DropItemCommand::~DropItemCommand() {}

void DropItemCommand::execute(ArgentumGame *game) {

  game->hero_drop_item(uid, item);
}