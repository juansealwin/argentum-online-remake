#include "heroes_manager.h"

HeroesManager::HeroesManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

HeroesManager::~HeroesManager() {}

void HeroesManager::update(std::map<unsigned int, Hero *> &heroes) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;
  // 4 actrualizaciones por segundo para los heroes (vida-mana regen)

  for (auto &hero : heroes) {
    //if esta meditando deberia ser mas rapido
    if (time_difference.count() >= 5000000000) {
      hero.second->regenerate();
      last_update_time = actual_time;
    }
    hero.second->clear_effects();
  }
}

void HeroesManager::remove_death_heroes(std::map<unsigned int, Hero *> &heroes,
                                        Map *map) {
  for (auto it = heroes.cbegin(); it != heroes.cend();) {
    if (it->second->alive == false) {
      int x_pos = it->second->x_position;
      int y_pos = it->second->y_position;
      map->empty_cell(x_pos, y_pos);
      delete it->second;
      it = heroes.erase(it++);
    } else {
      ++it;
    }
  }
}
