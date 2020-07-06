#ifndef MONSTERS_MANAGER_H
#define MONSTERS_MANAGER_H
#include <chrono>
#include "monsters_factory.h"
#include "monster.h"

class MonstersManager {
 public:
  MonstersManager();
  ~MonstersManager();
  MonstersManager(const MonstersManager &) = delete;
  void update(std::map<unsigned int, Monster *> &monsters);
  void remove_death_monsters(std::map<unsigned int, Monster *> &monsters,
                             Map &map);
  void respawn_monsters(std::map<unsigned int, Monster *> &monsters, Map &map,
                        unsigned int total_monster_poblation,
                        Json::Value &monsters_cfg, unsigned int &entities_ids);

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
};

#endif  // MONSTERS_MANAGER_H
