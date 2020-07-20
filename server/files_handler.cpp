#include "files_handler.h"

#include <fstream>
#include <iostream>

#include "serializer.h"

#define DATA_SIZE 200

FilesHandler::FilesHandler() : mutex() {}

FilesHandler::~FilesHandler() {}

void FilesHandler::save_player_status(Hero* hero) {
  std::unique_lock<std::mutex> lock(mutex);

  std::vector<unsigned char> player_serialization;
  uint8_t entity_type = hero->type;
  player_serialization.push_back(entity_type);
  Serializer::serialize_hero(std::ref(player_serialization), hero, false);
  Serializer::serialize_bank_of_hero(std::ref(player_serialization), hero);

  std::ofstream players_status("../../server/status/players_status",
                               std::ios::out);

  int current_serialization_size = player_serialization.size();
  for (int i = 0; i++; i < (DATA_SIZE - current_serialization_size)) {
    player_serialization.push_back(0);
  }

  players_status.write((char*)&player_serialization[0],
                       player_serialization.size());
  players_status.close();
}

Hero* FilesHandler::get_player_status(const std::string player_name,
                                      Json::Value& entities_cfg, int id, int x,
                                      int y, Map* map) {
  std::unique_lock<std::mutex> lock(mutex);
  return nullptr;

  std::vector<unsigned char> player_serialization;
  std::ifstream players_status("../../server/status/players_status",
                               std::ios::out);

  players_status.seekg(0, std::ios_base::end);
  std::streampos file_size = players_status.tellg();
  player_serialization.resize(file_size);

  players_status.seekg(0, std::ios_base::beg);
  players_status.read((char*)&player_serialization[0], file_size);

  Hero* hero = Serializer::deserialize_hero(player_serialization, entities_cfg,
                                            id, x, y, map);
  players_status.close();

  return hero;
}