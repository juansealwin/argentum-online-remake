#include "files_handler.h"

FilesHandler::FilesHandler() : mutex() {}

FilesHandler::~FilesHandler() {}

void FilesHandler::save_player_status(Hero* hero) {
  std::unique_lock<std::mutex> lock(mutex);

  std::vector<unsigned char> player_serialization;
  uint8_t entity_type = hero->type;
  player_serialization.push_back(entity_type);
  // Serializer::serialize_hero(std::ref(player_serialization), hero);
  // Serializer::serialize_bank_of_hero(std::ref(player_serialization), hero);

  std::ofstream players_status(
      "../../server/status/players_status",
      std::ios::out | std::ios::binary | std::ios::app);
  // std::ofstream players_file_position(
  //     "../../server/status/players_file_position");

  // players_status.write(reinterpret_cast<unsigned char*>(&players_status),
  //                      sizeof(player_serialization))

  //     std::copy(player_serialization.cbegin(), player_serialization.cend(),
  //               std::ostreambuf_iterator<char>(players_status));

  players_status.write((char*)&player_serialization[0],
                       player_serialization.size());
  players_status.close();
}

Hero* FilesHandler::get_player_status(const std::string player_name) {
  std::unique_lock<std::mutex> lock(mutex);

  std::vector<unsigned char> player_serialization;
  std::ifstream players_status("../../server/status/players_status");

  // std::ostringstream ss;
  // ss << players_status.rdbuf();
  // const std::string& s = ss.str();
  // std::vector<unsigned char> player_serialization(s.begin(), s.end());

  players_status.seekg(0, std::ios_base::end);
  std::streampos fileSize = players_status.tellg();
  player_serialization.resize(fileSize);

  players_status.seekg(0, std::ios_base::beg);
  players_status.read((char*)&player_serialization[0], fileSize);

  Hero* hero = Deserializer::deserialize_hero(player_serialization);
  players_status.close();

  return hero;
}
