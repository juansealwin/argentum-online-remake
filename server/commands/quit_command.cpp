#include "quit_command.h"
#include <iostream>
QuitCommand::QuitCommand(const unsigned int uid) : Command(uid) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(ArgentumGame *game) {
  // TO DO: guardar estado del jugador 
  game->stop_notification_queue(uid);
  game->clean_notifications_queues();
  game->kill_player(uid);
}
