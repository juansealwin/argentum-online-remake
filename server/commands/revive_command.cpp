#include "revive_commad.h"
#include <iostream>
ReviveCommand::ReviveCommand(const unsigned int uid) : Command(uid) {}

ReviveCommand::~ReviveCommand() {}

void ReviveCommand::execute(ArgentumGame *game) {
  game->hero_revive(uid);
}
