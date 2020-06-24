#ifndef PROTECTED_MAP_H
#define PROTECTED_MAP_H

#include <condition_variable>
#include <mutex>
#include "game.h"
#include "character_status.h"

class ProtectedMap {
 private:
  Game* read_map;
  Game* write_map;
  std::map<int, CharacterStatus> current_status;
  std::mutex block_maps;
  std::condition_variable cv;

 public:
  ProtectedMap();
  ~ProtectedMap();
  Game map_reader();
  void map_writer(std::map<int, CharacterStatus>&);
};

#endif