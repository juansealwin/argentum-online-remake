#include "files_handler.h"

#include <fstream>
#include <iostream>

#include "serializer.h"

FilesHandler::FilesHandler() : mutex() {}

FilesHandler::~FilesHandler() {}

void FilesHandler::save_player_status(Hero* hero) {
  std::unique_lock<std::mutex> lock(mutex);

  std::vector<unsigned char> player_serialization;
  Serializer::serialize_hero(std::ref(player_serialization), hero);
  Serializer::serialize_bank_of_hero(std::ref(player_serialization), hero);

  std::ofstream players_status;
  std::ofstream players_file_position;
  players_status.open("../../server/status/players_status");
  players_file_position.open("../../server/status/players_file_position");

  std::cout << players_status.is_open() << std::endl;
  std::copy(player_serialization.cbegin(), player_serialization.cend(),
            std::ostreambuf_iterator<char>(players_status));
  players_status.close();
}
