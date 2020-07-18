#include "bank_gold_command.h"

BankGoldCommand::BankGoldCommand(const unsigned int uid, const int ammount) : Command(uid), ammount(ammount) {

}

BankGoldCommand::~BankGoldCommand() {}

void BankGoldCommand::execute(ArgentumGame *game) {
  game->hero_bank_gold(uid, ammount);
}