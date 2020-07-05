#ifndef DROPS_MANAGER_H
#define DROPS_MANAGER_H
#include "drop.h"
#include "item_factory.h"
class DropsManager {
 public:
  DropsManager();
  ~DropsManager();
  DropsManager(const DropsManager &) = delete;

  void create_drops(std::map<unsigned int, Hero *> &heroes,
              std::map<unsigned int, Monster *> &monsters,
              std::map<std::tuple<unsigned int, unsigned int>, Drop*> &drops, Json::Value items_config);
  void add_monster_drops(std::map<unsigned int, Monster *> &monsters,
              std::map<std::tuple<unsigned int, unsigned int>, Drop*> &drops, Json::Value items_config);
  void add_heroes_drops(std::map<unsigned int, Hero *> &heroes, std::map<std::tuple<unsigned int, unsigned int>, Drop*> &drops);
  void remove_old_and_empty_drops(
      std::map<std::tuple<unsigned int, unsigned int>, Drop*> &drops);
};

#endif  // DROPS_MANAGER_H
