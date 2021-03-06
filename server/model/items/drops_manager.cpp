#include "drops_manager.h"

DropsManager::DropsManager() {}

DropsManager::~DropsManager() {}

void DropsManager::create_drops(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config, unsigned int &entities_ids) {
  add_monster_drops(monsters, drops, items_config, entities_ids);
  add_heroes_drops(heroes, drops, items_config, entities_ids);
}

void DropsManager::add_monster_drops(
    std::map<unsigned int, Monster *> &monsters,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config, unsigned int &entities_ids) {
  std::map<unsigned int, Monster *>::iterator it = monsters.begin();
  while (it != monsters.end()) {
    if (it->second->is_death()) {
      randomly_add_drop(it->second, drops, items_config, entities_ids);
    }
    ++it;
  }
}

void DropsManager::add_drop(
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops, Item *i,
    std::tuple<unsigned int, unsigned int> pos, Json::Value items_config,
    unsigned int &entities_ids) {
  Drop *drop;
  if (drops.count(pos) > 0) {
    drop = drops.at(pos);
    drop->add_item(i);
  } else {
    drop = new Drop(items_config["drop"]["id"].asUInt(), entities_ids++, i, 0);
    drops.emplace(pos, drop);
  }
}

void DropsManager::add_heroes_drops(
    std::map<unsigned int, Hero *> &heroes,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config, unsigned int &entities_ids) {
  std::map<unsigned int, Hero *>::iterator it = heroes.begin();
  while (it != heroes.end()) {
    if (it->second->is_death() && (it->second->has_items_in_inventory() ||
                                   it->second->has_excedent_coins())) {
      std::tuple<unsigned int, unsigned int> drop_coordinates =
          std::tuple<unsigned int, unsigned int>(it->second->x_position,
                                                 it->second->y_position);
      Drop *drop;
      Inventory *inv = it->second->inventory;
      unsigned int gold = it->second->remove_excess_gold();
      if (drops.count(drop_coordinates) > 0) {
        drop = drops.at(drop_coordinates);
        drop->add_items(inv);
        drop->add_gold(gold);
      } else {
        drop = new Drop(items_config["drop"]["id"].asUInt(), entities_ids++,
                        inv, gold);
        drops.emplace(drop_coordinates, drop);
      }
    }
    ++it;
  }
}
void DropsManager::remove_old_and_empty_drops(
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops) {
  // TO DO: Chequear hace cuanto fueron creados los drops y eliminarlos
  for (auto it = drops.cbegin(); it != drops.cend();) {
    if (it->second->is_empty()) {
      delete it->second;
      it = drops.erase(it++);
    } else {
      ++it;
    }
  }
}

void DropsManager::randomly_add_drop(
    Monster *dead_monster,
    std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
    Json::Value items_config, unsigned int &entities_ids) {
  int rand_int = HelperFunctions::random_int(0, 9);
  Drop *drop = nullptr;
  if (rand_int < 8) {
    std::tuple<unsigned int, unsigned int> drop_coordinates =
        std::tuple<unsigned int, unsigned int>(dead_monster->x_position,
                                               dead_monster->y_position);

    Item *item = ItemFactory::create_random_item(items_config);
    rand_int = HelperFunctions::random_int(0, 9);
    unsigned int gold = 0;
    if (rand_int <
        DROP_RATE) {  // 30% de probabilidades de agregar monedas al drop
      gold = rand_int * dead_monster->max_hp;
    }
    if (drops.count(drop_coordinates) > 0) {
      drop = drops.at(drop_coordinates);
      drop->add_item(item);
      drop->add_gold(gold);
    } else {
      Drop *drop = new Drop(items_config["drop"]["id"].asUInt(), entities_ids++,
                            item, gold);
      drops.emplace(drop_coordinates, drop);
    }
  }
}
