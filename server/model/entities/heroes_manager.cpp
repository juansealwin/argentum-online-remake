#include "heroes_manager.h"

HeroesManager::HeroesManager() {
  last_update_time = last_move_time = std::chrono::high_resolution_clock::now();
}

HeroesManager::~HeroesManager() {}

void HeroesManager::update(std::map<unsigned int, Hero *> &heroes,
                           const int nanoseconds_for_regenerating_hero,
                           const int nanoseconds_for_automove_hero) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto update_time_diff = actual_time - last_update_time;
  auto move_time_diff = actual_time - last_move_time;
  // 4 actualizaciones por segundo para los heroes (vida-mana regen)

  for (auto &hero : heroes) {
    hero.second->try_to_unblock();
    if (update_time_diff.count() >= nanoseconds_for_regenerating_hero) {
      hero.second->regenerate();
      last_update_time = actual_time;
    }
    if (move_time_diff.count() >= nanoseconds_for_automove_hero) {
      hero.second->auto_move();
      last_move_time = actual_time;
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
