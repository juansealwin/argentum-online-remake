#ifndef HERO_MANAGER_H
#define HERO_MANAGER_H
#include <chrono>

#include "hero.h"
class HeroesManager {
 public:
  HeroesManager();
  ~HeroesManager();
  HeroesManager(const HeroesManager &) = delete;
  void update(std::map<unsigned int, Hero *> &heroes,
              const int nanoseconds_for_regenerating_hero,
              const int nanoseconds_for_automove_hero);
  void clear_effects(std::map<unsigned int, Hero *> &heroes);
  void remove_death_heroes(std::map<unsigned int, Hero *> &heroes, Map *map);

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_move_time;
};

#endif  // HERO_MANAGER_H
