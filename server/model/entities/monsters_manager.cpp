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

void MonstersManager::remove_death_monsters(std::map<unsigned int, Monster *> &monsters, Map *map) {
  for (auto it = monsters.cbegin(); it != monsters.cend();) {
    if (it->second->alive == false) {
      int x_pos = it->second->x_position;
      int y_pos = it->second->y_position;
      map->empty_cell(x_pos, y_pos);
      delete it->second;
      it = monsters.erase(it++);
    } else {
      ++it;
    }
  }
}
