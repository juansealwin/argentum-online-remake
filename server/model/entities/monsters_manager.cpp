#include "monsters_manager.h"

#include "hero.h"
MonstersManager::MonstersManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

MonstersManager::~MonstersManager() {}

void MonstersManager::update(std::map<unsigned int, Monster *> &monsters,
                             std::map<unsigned int, Hero *> heroes) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;

  for (auto &monster : monsters) {
    if (time_difference.count() >= 1000000000) {
      last_update_time = actual_time;
      for (auto &hero : heroes) {
        if (!hero.second->is_death()) {
          attack_or_move_to_hero(monster.second, hero.second);
        }
      }
      monster.second->auto_move();
    }
    monster.second->clear_effects();
  }
}

void MonstersManager::attack_or_move_to_hero(Monster *m, Hero *h) {
  if (m->is_next_to(h->x_position, h->y_position)) {
    std::cout << "monster is next to hero!!!" << std::endl;
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
