#include "drops_manager.h"

DropsManager::DropsManager() {}

DropsManager::~DropsManager() {}

void DropsManager::create_drops(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config) {
  add_monster_drops(monsters, drops, items_config);
  add_heroes_drops(heroes, drops);
}

void DropsManager::add_monster_drops(
    std::map<unsigned int, Monster *> &monsters,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config) {
  std::map<unsigned int, Monster *>::iterator it = monsters.begin();
  while (it != monsters.end()) {
    if (it->second->is_death()) {
      // crear funcion create random drop que contemple la probabilidad de 0.8
      // de dropear nada
      std::tuple<unsigned int, unsigned int> drop_coordinates =
          std::tuple<unsigned int, unsigned int>(it->second->x_position,
                                                 it->second->y_position);
      Item *item = ItemFactory::create_random_item(items_config);
      Drop *drop = new Drop(item);
      drops.emplace(drop_coordinates, drop);
      std::cout << "Created drop from monster!!" << std::endl;
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
      std::tuple<unsigned int, unsigned int> drop_coordinates =
          std::tuple<unsigned int, unsigned int>(it->second->x_position,
                                                 it->second->y_position);
      Drop *drop = new Drop(it->second->inventory);
      if (!drop->is_empty()) drops.emplace(drop_coordinates, drop);
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