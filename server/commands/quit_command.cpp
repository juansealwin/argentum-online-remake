#include "quit_command.h"

#include <iostream>

QuitCommand::QuitCommand(const unsigned int uid) : Command(uid) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(ArgentumGame *game) {
  // Hero *hero = game->get_hero_by_id(uid);
  // game->files_handler.save_player_status(hero);

  game->stop_notification_queue(uid);
  game->clean_notifications_queues();
  game->kill_player(uid);
}
