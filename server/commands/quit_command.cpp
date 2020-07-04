#include "quit_command.h"
#include <iostream>
QuitCommand::QuitCommand(const unsigned int player_id) : Command(player_id) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(ArgentumGame *game) {
  // TO DO: guardar estado del jugador 
  std::cout << "executing quit command" << std::endl;
  game->clean_notifications_queues();
  game->kill_player(uid);
}
