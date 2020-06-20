#ifndef BLOCKINGMAP_H
#define BLOCKINGMAP_H
#include <condition_variable>
#include <map>
#include <iostream>
#include <mutex>
#include "character_status.h"
#include "event.h"

class BlockingMap {
 private:
  std::map<int, CharacterStatus> map;
  std::mutex block_map;
  std::condition_variable cv;
  bool more_updates = true;

 public:
  BlockingMap();
  ~BlockingMap();
  BlockingMap(BlockingMap&) = delete;
  void update_map(std::map<int, CharacterStatus>&);
  void read_map(std::map<int, CharacterStatus>&);
  void no_more_updates();
  BlockingMap& operator=(const BlockingMap&) = delete;
};
#endif
