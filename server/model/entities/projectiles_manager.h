#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H
#include "map.h"
#include "projectile.h"
#include "monster.h"
#include "hero.h"
class Hero;
class Monster;
class Projectile;
class ProjectileManager {
 public:
  ProjectileManager();
  ~ProjectileManager();
  ProjectileManager(const ProjectileManager &) = delete;

  void update(std::map<unsigned int, Hero *> &heroes,
              std::map<unsigned int, Monster *> &monsters,
              std::map<unsigned int, Projectile *> &projectiles);
};

#endif  // PROJECTILE_MANAGER_H
