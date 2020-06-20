#include "blocking_map.h"

BlockingMap::BlockingMap() {}

BlockingMap::~BlockingMap() {}

void BlockingMap::updateMap(std::map<int, CharacterStatus>& updated) {
  std::unique_lock<std::mutex> lock(block_map);

  std::map<int, CharacterStatus>::iterator it;
  std::map<int, CharacterStatus>::iterator it2;

  for (it = updated.begin(); it != updated.end(); it++) {
    it2 = map.find(it->first);
    // Chequeamos si la entidad existe
    if (it2 != map.end()) {
      it2->second = it->second;
    } else {
      map[it->first] = it->second;
    }
  }
  cv.notify_all();
}

void BlockingMap::readMap(std::map<int, CharacterStatus>& to_update) {
  std::unique_lock<std::mutex> lock(block_map);

  while (map.empty()) {
    cv.wait(lock);
  }
  // If the thread wake up because there won't be more
  // events then it must return
  if (no_more_updates && map.empty()) {
    return;
  }
  std::map<int, CharacterStatus>::iterator it;
  std::map<int, CharacterStatus>::iterator it2;
  for (it = map.begin(); it != map.end(); it++) {
    it2 = to_update.find(it->first);
    if (it2 != map.end()) {
      it2->second = it->second;
    } else {
      to_update[it->first] = it->second;
    }
  }
}

void BlockingMap::noMoreUpdates() {
  no_more_updates = true;
  cv.notify_all();
}
