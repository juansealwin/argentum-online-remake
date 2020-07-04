#include "attack_command.h"
#include <iostream>
AttackCommand::AttackCommand(const unsigned int player_id) : Command(player_id) {}

AttackCommand::~AttackCommand() {}

void AttackCommand::execute(ArgentumGame *game) {
  // TODO
  std::cout << "executing attack command" << std::endl;
  game->throw_projectile(uid);
}
