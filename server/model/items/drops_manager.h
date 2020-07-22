#ifndef DROPS_MANAGER_H
#define DROPS_MANAGER_H
#include "drop.h"
#include "helper_functions.h"
#include "item_factory.h"
#define DROP_RATE 3

class DropsManager {
 public:
  DropsManager();
  ~DropsManager();
  DropsManager(const DropsManager &) = delete;

  void create_drops(
      std::map<unsigned int, Hero *> &heroes,
      std::map<unsigned int, Monster *> &monsters,
      std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
      Json::Value items_config, unsigned int &entities_ids);
  void add_monster_drops(
      std::map<unsigned int, Monster *> &monsters,
      std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
      Json::Value items_config, unsigned int &entities_ids);
  void add_heroes_drops(
      std::map<unsigned int, Hero *> &heroes,
      std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
      Json::Value items_config, unsigned int &entities_ids);
  void remove_old_and_empty_drops(
      std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops);
  void add_drop(std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
                Item *i, std::tuple<unsigned int, unsigned int> pos,
                Json::Value items_config, unsigned int &entities_ids);

 private:
  // Agrega un drop con 80% de probabilidad
  void randomly_add_drop(
      Monster *dead_monster,
      std::map<std::tuple<unsigned int, unsigned int>, Drop *> &drops,
      Json::Value items_config, unsigned int &entities_ids);
};

#endif  // DROPS_MANAGER_H
