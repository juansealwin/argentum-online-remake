#ifndef FILES_HANDLER_H
#define FILES_HANDLER_H

#include <string>
#include <unordered_map>

#include "hero.h"

class FilesHandler {
 private:
  std::unordered_map<std::string, int> get_players_positions_map();
  void save_players_positions_map(std::unordered_map<std::string, int>& map);

 public:
  FilesHandler();
  ~FilesHandler();
  void save_player_status(Hero* hero);
  Hero* get_player_status(const std::string player_name,
                          Json::Value& entities_cfg, int id, int x, int y,
                          Map* map);
};

#endif
