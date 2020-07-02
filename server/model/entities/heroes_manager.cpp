#include "heroes_manager.h"

HeroesManager::HeroesManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

HeroesManager::~HeroesManager() {}

void HeroesManager::update(std::map<unsigned int, Hero *> &heroes) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;
  // 4 actrualizaciones por segundo para los heroes (vida-mana regen)
  if (time_difference.count() >= 250000000) {
    for (auto &hero : heroes) {
      hero.second->update();
    }
  }
}
