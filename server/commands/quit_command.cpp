#include "quit_command.h"

#include <iostream>
#include <vector>

QuitCommand::QuitCommand(const unsigned int uid) : Command(uid) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(ArgentumGame *game) {
  Hero *hero = game->get_hero_by_id(uid);
  std::vector<unsigned char> player_serialization =
      game->files_handler.get_serialization_of_hero(hero);
  std::tuple<std::string, std::vector<unsigned char>> *player =
      new std::tuple<std::string, std::vector<unsigned char>>(
          hero->get_name(), player_serialization);
  game->add_player_to_save(player);

  game->stop_notification_queue(uid);
  game->clean_notifications_queues();
  game->kill_player(uid);
}
