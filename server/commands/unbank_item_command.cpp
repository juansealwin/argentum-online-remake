#include "unbank_item_command.h"

UnbankItemCommand::UnbankItemCommand(const unsigned int uid, const int item) : Command(uid), item(item) {}

void UnbankItemCommand::execute(ArgentumGame *game) {
  game->hero_unbank_item(uid, item);
}
