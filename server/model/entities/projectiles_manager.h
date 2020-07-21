#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H
#include <chrono>
#include <string>

#include "hero.h"
#include "map.h"
#include "message_center.h"
#include "monster.h"
#include "projectile.h"
class ProjectileManager {
 public:
  ProjectileManager();
  ~ProjectileManager();
  ProjectileManager(const ProjectileManager &) = delete;

  void update(std::map<unsigned int, Hero *> &heroes,
              std::map<unsigned int, Monster *> &monsters,
              std::map<unsigned int, Projectile *> &projectiles,
              MessageCenter &message_center, Json::Value &game_cfg);
  void remove_death_projectiles(
      std::map<unsigned int, Projectile *> &projectiles, Map *map);

 private:
  void manage_collision(Projectile *projectile,
                        std::map<unsigned int, Hero *> &heroes,
                        std::map<unsigned int, Monster *> &monsters,
                        MessageCenter &message_center, Json::Value &game_cfg);
  BaseCharacter *get_hero_or_monster(
      int uid, std::map<unsigned int, Hero *> &heroes,
      std::map<unsigned int, Monster *> &monsters);

  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
};

#endif  // PROJECTILE_MANAGER_H
