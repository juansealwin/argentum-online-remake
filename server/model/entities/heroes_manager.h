#ifndef HERO_MANAGER_H
#define HERO_MANAGER_H
#include "hero.h"
#include <chrono>
class HeroesManager {
 public:
  HeroesManager();
  ~HeroesManager();
  HeroesManager(const HeroesManager &) = delete;
  void update(std::map<unsigned int, Hero *> &heroes);
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
};

#endif  // HERO_MANAGER_H
