#include "projectiles_manager.h"

ProjectileManager::ProjectileManager() {}

ProjectileManager::~ProjectileManager() {}

void ProjectileManager::update(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<unsigned int, Projectile *> &projectiles) {
  for (auto it = projectiles.cbegin(); it != projectiles.cend();) {
    std::cout << "iterating projectiles" << std::endl;
    Projectile *projectile = it->second;
    projectile->update();
    if (projectile->collided) {
      manage_collision(projectile, heroes, monsters);
    }
    if (it->second->alive == false) {
      it = projectiles.erase(it++);
    } else {
      ++it;
    }
  }
}

void ProjectileManager::manage_collision(
    Projectile *projectile, std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters) {

  int attacked_player_id = projectile->get_collided_entity();
  BaseCharacter *attacked_entity =
      get_hero_or_monster(attacked_player_id, heroes, monsters);
  if (attacked_entity) {
    if (!attacked_entity->is_death()) {
      unsigned int damage_done = attacked_entity->receive_damage(
          projectile->get_damage(), projectile->is_critical());
      int attacker_player_id = projectile->get_attacker_id();
      BaseCharacter *attacker = get_hero_or_monster(attacker_player_id, heroes, monsters);
      if (attacker) attacker->notify_damage_done(attacked_entity, damage_done);
    }
  }
  projectile->kill();
}

BaseCharacter* ProjectileManager::get_hero_or_monster(
    int uid, std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters) {
      std::cout << "getting hero or monster.." << std::endl;
  BaseCharacter *c = nullptr;
  if (heroes.count(uid) > 0) {
    c = dynamic_cast<BaseCharacter *>(heroes.at(uid));
  } else if (monsters.count(uid) > 0) {
    c = dynamic_cast<BaseCharacter *>(monsters.at(uid));
  }
  return c;
}