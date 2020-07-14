#include "use_item_special_command.h"
#include <iostream>
UseItemSpecialCommand::UseItemSpecialCommand(const unsigned int uid) : Command(uid) {}

UseItemSpecialCommand::~UseItemSpecialCommand() {}

void UseItemSpecialCommand::execute(ArgentumGame *game) {
  game->hero_use_special(uid);
}
