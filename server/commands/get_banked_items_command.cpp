#include "get_banked_items_command.h"

GetBankedItemsCommand::GetBankedItemsCommand(const unsigned int uid)
    : Command(uid) {}

void GetBankedItemsCommand::execute(ArgentumGame *game) {
  game->hero_get_closest_npc_info(uid);
}

GetBankedItemsCommand::~GetBankedItemsCommand() {}