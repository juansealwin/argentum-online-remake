#include "monsters_manager.h"

MonstersManager::MonstersManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

MonstersManager::~MonstersManager() {}

void MonstersManager::update(std::map<unsigned int, Monster *> &monsters) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;
  if (time_difference.count() >= 1000000000) {  // paso un segundo (mover a cfg)
    for (auto &monster : monsters) {
      monster.second->update();
      last_update_time = actual_time;
    }
  }
}
