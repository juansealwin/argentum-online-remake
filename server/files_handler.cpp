#include "files_handler.h"

#include <fstream>
#include <iostream>
#include <msgpack.hpp>
#include <unordered_map>

#include "serializer.h"

#define DATA_SIZE 200

FilesHandler::FilesHandler() : mutex() {}

FilesHandler::~FilesHandler() {}

void hola() {
  std::unordered_map<std::string, int> map = {
      {"Rodrigo", 1}, {"sdssds", 21212}, {"FEfplepelfp", 848}};
  std::stringstream buffer;
  msgpack::pack(buffer, map);
  std::ofstream players_file_position(
      "../../server/status/players_file_position", std::ios::binary);
  players_file_position << buffer.rdbuf();
  players_file_position.close();
}

void chau() {
  std::vector<unsigned char> buffer;
  std::ifstream players_file_position(
      "../../server/status/players_file_position", std::ios::binary);
  players_file_position.seekg(0, std::ios_base::end);
  std::streampos file_size = players_file_position.tellg();
  std::cout << file_size << std::endl;
  buffer.resize(file_size);
  players_file_position.seekg(0, std::ios_base::beg);
  players_file_position.read((char*)&buffer[0], file_size);
  const std::string buffer_str(buffer.begin(), buffer.end());
  const char* buffer_chars = buffer_str.c_str();
  msgpack::object_handle oh =
      msgpack::unpack(buffer_chars, buffer_str.size());
  msgpack::object deserialized = oh.get();
  std::unordered_map<std::string, int> map;
  deserialized.convert(map);
  std::unordered_map<std::string, int> expected_map = {
      {"Rodrigo", 1}, {"sdssds", 21212}, {"fEfplepelfp", 848}};
  const bool equal = expected_map == map;
  std::cout << "son iguales? " << equal << std::endl;
}

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
  hola();
  chau();
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