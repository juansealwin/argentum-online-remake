#ifndef MONSTERS_MANAGER_H
#define MONSTERS_MANAGER_H
#include "monster.h"
#include <chrono>
class MonstersManager {
 public:
  MonstersManager();
  ~MonstersManager();
  MonstersManager(const MonstersManager &) = delete;
  void update(std::map<unsigned int, Monster *> &monsters);
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
};

#endif  // MONSTERS_MANAGER_H
