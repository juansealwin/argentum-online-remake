#include "buy_item_command.h"

BuyItemCommand::BuyItemCommand(const unsigned int uid, const int item) : Command(uid), item(item) {

}

BuyItemCommand::~BuyItemCommand() {}

void BuyItemCommand::execute(ArgentumGame *game) {
  game->hero_buy_item(uid, item);
}