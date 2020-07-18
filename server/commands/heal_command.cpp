#include "heal_command.h"
#include <iostream>
HealCommand::HealCommand(const unsigned int uid) : Command(uid) {}

HealCommand::~HealCommand() {}

void HealCommand::execute(ArgentumGame *game) {
  game->hero_heal(uid);
}
