#ifndef PROTECTED_MAP_H
#define PROTECTED_MAP_H

#include <condition_variable>
#include <mutex>
#include "game.h"
#include "character_status.h"
#include "types.h"

class ProtectedMap {
 private:
  Game* read_map;
  Game* write_map;
  std::map<int, CharacterStatus> current_status;
  std::mutex block_maps;
  std::condition_variable cv;

 public:
  ProtectedMap(int, int, int);
  ~ProtectedMap();
  Game map_reader();
  void copy_buffer();
  void map_writer(std::map<int, CharacterStatus>&);
};

#endif