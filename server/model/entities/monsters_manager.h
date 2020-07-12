#ifndef MONSTERS_MANAGER_H
#define MONSTERS_MANAGER_H
#include <chrono>

#include "monster.h"
#include "monsters_factory.h"
#include "message_center.h"
class Hero;
class MonstersManager {
 public:
  MonstersManager();
  ~MonstersManager();
  MonstersManager(const MonstersManager &) = delete;
  void update(std::map<unsigned int, Monster *> &monsters,
              std::map<unsigned int, Hero *> heroes,
              MessageCenter &message_center);
  void remove_death_monsters(std::map<unsigned int, Monster *> &monsters,
                             Map *map);
  void respawn_monsters(std::map<unsigned int, Monster *> &monsters, Map *map,
                        unsigned int total_monster_poblation,
                        Json::Value &monsters_cfg, unsigned int &entities_ids);

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
  bool attack_or_move_to_hero(Monster* m, Hero* h, MessageCenter &message_center);
};

#endif  // MONSTERS_MANAGER_H
