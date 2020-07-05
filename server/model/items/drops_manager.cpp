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
      create_random_drop(it->second, drops, items_config);
      // std::tuple<unsigned int, unsigned int> drop_coordinates =
      //     std::tuple<unsigned int, unsigned int>(it->second->x_position,
      //                                            it->second->y_position);
      // Item *item = ItemFactory::create_random_item(items_config);
      // Drop *drop = new Drop(item, 0);
      // drops.emplace(drop_coordinates, drop);
      // std::cout << "Created drop from monster!!" << std::endl;
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
      Drop *drop =
          new Drop(it->second->inventory, it->second->remove_surplus_coins());
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

void DropsManager::create_random_drop(
    Monster *dead_monster,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config) {
      std::cout << "trying to create random drop" << std::endl;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, 9);
  int rand_int = distribution(generator);
  Drop *drop = nullptr;
  if (rand_int < 8) {
      std::cout << "creating random drop" << std::endl;

    std::tuple<unsigned int, unsigned int> drop_coordinates =
        std::tuple<unsigned int, unsigned int>(dead_monster->x_position,
                                               dead_monster->y_position);
    Item *item = ItemFactory::create_random_item(items_config);
    rand_int = distribution(generator);
    unsigned int coins = 0;
    if (rand_int < 3) { //30% de probabilidades de agregar monedas al drop
      coins = rand_int * dead_monster->max_hp;
    }
    Drop *drop = new Drop(item, coins);
    drops.emplace(drop_coordinates, drop);
    
  }
}