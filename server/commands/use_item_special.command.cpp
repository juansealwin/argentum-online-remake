#include "use_item_special_command.h"
#include <iostream>
UseItemSpecial::UseItemSpecial(const unsigned int uid) : Command(uid) {}

UseItemSpecial::~UseItemSpecial() {}

void UseItemSpecial::execute(ArgentumGame *game) {
  game->hero_use_special(uid);
}
