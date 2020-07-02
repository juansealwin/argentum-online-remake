#include "projectiles_manager.h"

ProjectileManager::ProjectileManager() {}

ProjectileManager::~ProjectileManager() {}

void ProjectileManager::update(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<unsigned int, Projectile *> &projectiles) {
  for (auto it = projectiles.cbegin(); it != projectiles.cend();) {
    Projectile *projectile = it->second;
    projectile->update();
    if (projectile->collided) {
    }
    if (it->second->alive == false) {
      it = projectiles.erase(it++);
    } else {
      // std::cout << "Proyectil sigue vivo: "
      //           << " x: " << it->second->x_position
      //           << " y: " << it->second->y_position << "Collided?"
      //           << it->second->collided << std::endl;
      ++it;
    }
  }
}

void ProjectileManager::manage_collision(
    Projectile *projectile, std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters) {
  int attacked_player_id = projectile->get_collided_entity();
  BaseCharacter *attacked_entity = nullptr;
  std::cout << "Attacked player id: " << attacked_player_id << std::endl;
  if (heroes.count(attacked_player_id) > 0) {
    attacked_entity =
        dynamic_cast<BaseCharacter *>(heroes.at(attacked_player_id));
  } else if (monsters.count(attacked_player_id) > 0) {
    attacked_entity =
        dynamic_cast<BaseCharacter *>(monsters.at(attacked_player_id));
  }
  if (attacked_entity) {
    if (!attacked_entity->is_death()) {
      unsigned int damage_done = attacked_entity->receive_damage(
          projectile->get_damage(), projectile->is_critical());
      int attacker_player_id = projectile->get_attacker_id();
      BaseCharacter *attacker = nullptr;
      std::cout << "Attacker player id: " << attacker_player_id << std::endl;
      if (heroes.count(attacker_player_id) > 0) {
        attacker = dynamic_cast<BaseCharacter *>(heroes.at(attacker_player_id));

      } else if (monsters.count(attacker_player_id) > 0) {
        std::cout << "trying to obtain monster" << std::endl;

        attacker =
            dynamic_cast<BaseCharacter *>(monsters.at(attacker_player_id));
      }
      if (attacker) attacker->notify_damage_done(attacked_entity, damage_done);
    }
  }
  projectile->kill();
}