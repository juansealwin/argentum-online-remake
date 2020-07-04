#include "drops_manager.h"

DropsManager::DropsManager() {}

DropsManager::~DropsManager() {}

void DropsManager::create_drops(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops) {
  add_monster_drops(monsters, drops);
  add_heroes_drops(heroes, drops);
}

void DropsManager::add_monster_drops(
    std::map<unsigned int, Monster *> &monsters,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops) {
  std::map<unsigned int, Monster *>::iterator it = monsters.begin();
  while (it != monsters.end()) {
    if (it->second->is_death()) {
      std::cout << "monster is dead, adding drop" << std::endl;
    }
    it++;
  }
}
void DropsManager::add_heroes_drops(
    std::map<unsigned int, Hero *> &heroes,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops) {
  std::map<unsigned int, Hero *>::iterator it = heroes.begin();
  while (it != heroes.end()) {
    if (it->second->is_death()) {
      std::cout << "hero is ghost, adding drop" << std::endl;
    }
    it++;
  }
}
void DropsManager::remove_old_and_empty_drops(
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops) {
  std::map<std::tuple<unsigned int, unsigned int>, Drop *>::iterator it =
      drops.begin();
  while (it != drops.end()) {
    if (it->second->is_empty()) {
      std::cout << "drop is empty, deleting it" << std::endl;
    }
    it++;
  }
}