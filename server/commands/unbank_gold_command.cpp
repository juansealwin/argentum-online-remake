#include "unbank_gold_command.h"

UnbankGoldCommand::UnbankGoldCommand(const unsigned int uid, const int ammount)
    : Command(uid),  ammount(ammount) {}

void UnbankGoldCommand::execute(ArgentumGame *game) {
  game->hero_unbank_gold(uid, ammount);
}
