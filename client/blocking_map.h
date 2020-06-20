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
  bool no_more_updates = false;

 public:
  BlockingMap();
  ~BlockingMap();
  BlockingMap(BlockingMap&) = delete;
  void updateMap(std::map<int, CharacterStatus>&);
  void readMap(std::map<int, CharacterStatus>&);
  void noMoreUpdates();
  BlockingMap& operator=(const BlockingMap&) = delete;
};
#endif
