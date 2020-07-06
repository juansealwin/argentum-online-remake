#include "monsters_manager.h"

MonstersManager::MonstersManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

MonstersManager::~MonstersManager() {}

void MonstersManager::update(std::map<unsigned int, Monster *> &monsters) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;

  for (auto &monster : monsters) {
    if (time_difference.count() >= 1000000000) {
      monster.second->auto_move();
      last_update_time = actual_time;
    }
    monster.second->clear_effects();
  }
}

void MonstersManager::remove_death_monsters(
    std::map<unsigned int, Monster *> &monsters, Map &map) {
  for (auto it = monsters.cbegin(); it != monsters.cend();) {
    if (it->second->alive == false) {
      int x_pos = it->second->x_position;
      int y_pos = it->second->y_position;
      map.empty_cell(x_pos, y_pos);
      delete it->second;
      it = monsters.erase(it++);
    } else {
      ++it;
    }
  }
}

void MonstersManager::respawn_monsters(
    std::map<unsigned int, Monster *> &monsters, Map &map,
    unsigned int total_monster_poblation, Json::Value &monsters_cfg,
    unsigned int &entities_ids) {
  while (monsters.size() < total_monster_poblation) {
    Monster *random_monster =
        MonstersFactory::create_random_monster(monsters_cfg, entities_ids, map);
    monsters.emplace(entities_ids++, random_monster);
  }
}
