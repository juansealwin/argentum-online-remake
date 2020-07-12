#include "bank_item_command.h"

BankItemCommand::BankItemCommand(const unsigned int uid, const int item) : Command(uid), item(item) {

}

BankItemCommand::~BankItemCommand() {}

void BankItemCommand::execute(ArgentumGame *game) {
  game->hero_bank_item(uid, item);
}