#include "pick_up_drop_command.h"

#include <iostream>

PickUpDropCommand::PickUpDropCommand(const unsigned int uid) : Command(uid) {}

PickUpDropCommand::~PickUpDropCommand() {}

void PickUpDropCommand::execute(ArgentumGame *game) {
  //std::cout << "executing pick up item command" << std::endl;
  game->pick_up_drop(uid);
}