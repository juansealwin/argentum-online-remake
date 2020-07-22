#include "files_handler.h"

#include <fstream>
#include <iostream>
#include <msgpack.hpp>

#include "serializer.h"

#define DATA_SIZE 200

FilesHandler::FilesHandler() : mutex() {}

FilesHandler::~FilesHandler() {}

void FilesHandler::save_players_positions_map(
    std::unordered_map<std::string, int>& map) {
  std::stringstream buffer;
  msgpack::pack(buffer, map);
  std::ofstream players_file_position(
      "../../server/status/players_file_position", std::ios::binary);
  players_file_position << buffer.rdbuf();
  players_file_position.close();
}

std::unordered_map<std::string, int> FilesHandler::get_players_positions_map() {
  std::unordered_map<std::string, int> map;
  std::vector<unsigned char> buffer;
  std::ifstream players_file_position(
      "../../server/status/players_file_position", std::ios::binary);
  players_file_position.seekg(0, std::ios_base::end);
  std::streampos file_size = players_file_position.tellg();

  if (file_size == 0) {
    return std::move(map);
  }

  buffer.resize(file_size);
  players_file_position.seekg(0, std::ios_base::beg);
  players_file_position.read((char*)&buffer[0], file_size);

  const std::string buffer_str(buffer.begin(), buffer.end());
  const char* buffer_chars = buffer_str.c_str();
  msgpack::object_handle oh = msgpack::unpack(buffer_chars, buffer_str.size());
  msgpack::object deserialized = oh.get();

  deserialized.convert(map);
  return std::move(map);
}

std::vector<unsigned char> FilesHandler::get_serialization_of_hero(Hero* hero) {
  std::vector<unsigned char> player_serialization;
  uint8_t entity_type = hero->type;
  player_serialization.push_back(entity_type);
  Serializer::serialize_hero(std::ref(player_serialization), hero, false);
  Serializer::serialize_bank_of_hero(std::ref(player_serialization), hero);
  int current_serialization_size = player_serialization.size();
  for (int i = 0; i < (DATA_SIZE - current_serialization_size); i++) {
    player_serialization.push_back('0');
  }
  return std::move(player_serialization);
}

void FilesHandler::save_player_status(
    std::vector<unsigned char>& player_serialization,
    const std::string player_name) {
  std::unique_lock<std::mutex> lock(mutex);
  std::unordered_map<std::string, int> players_positions =
      get_players_positions_map();
  const std::unordered_map<std::string, int>::const_iterator result =
      players_positions.find(player_name);
  int position = 0;
  if (result != players_positions.end()) {
    position = result->second;
  } else {
    if (!players_positions.empty()) {
      int last_position = players_positions.at("last_position");
      position = last_position + DATA_SIZE;
    }
    players_positions[player_name] = position;
    players_positions["last_position"] = position;
    save_players_positions_map(players_positions);
  }

  std::ofstream players_status("../../server/status/players_status",
                               std::ios::binary | std::ios::out | std::ios::in);
  players_status.seekp(position);
  players_status.write((char*)&player_serialization[0],
                       player_serialization.size());
  players_status.close();
}

Hero* FilesHandler::get_player_status(const std::string player_name,
                                      Json::Value& entities_cfg, int id, int x,
                                      int y, Map* map) {
  std::unique_lock<std::mutex> lock(mutex);
  std::unordered_map<std::string, int> players_positions =
      get_players_positions_map();
  const std::unordered_map<std::string, int>::const_iterator result =
      players_positions.find(player_name);

  if (result == players_positions.end()) {
    return nullptr;
  }

  const int position = result->second;
  std::cout << "leyendo a " << player_name << " en: " << position << std::endl;

  std::ifstream players_status("../../server/status/players_status",
                               std::ios::binary);
  std::vector<unsigned char> player_serialization;
  player_serialization.resize(DATA_SIZE);
  players_status.seekg(position);
  players_status.read((char*)&player_serialization[0], DATA_SIZE);

  Hero* hero = Serializer::deserialize_hero(player_serialization, entities_cfg,
                                            id, x, y, map);
  players_status.close();

  return hero;
}
