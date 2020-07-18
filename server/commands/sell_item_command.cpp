#include "sell_item_command.h"

SellItemCommand::SellItemCommand(const unsigned int uid, const int item)
    : Command(uid), item(item) {}

SellItemCommand::~SellItemCommand() {}

void SellItemCommand::execute(ArgentumGame *game) {
  game->hero_sell_item(uid, item);
}