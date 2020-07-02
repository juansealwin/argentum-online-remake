#include "projectiles_manager.h"

ProjectileManager::ProjectileManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

ProjectileManager::~ProjectileManager() {}

void ProjectileManager::update(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<unsigned int, Projectile *> &projectiles) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;
  // 4 movimientos por segundo para los proyectiles
  if (time_difference.count() >= 93750000) {
    for (auto &projectile : projectiles) {
      Projectile *p = projectile.second;
      p->auto_move();
      if (p->collided) {
        manage_collision(p, heroes, monsters);
      }
    }
    last_update_time = actual_time;
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
      BaseCharacter *attacker =
          get_hero_or_monster(attacker_player_id, heroes, monsters);
      if (attacker) attacker->notify_damage_done(attacked_entity, damage_done);
    }
  }
  projectile->kill();
}

BaseCharacter *ProjectileManager::get_hero_or_monster(
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

void ProjectileManager::remove_death_projectiles(
    std::map<unsigned int, Projectile *> &projectiles, Map *map) {
  for (auto it = projectiles.cbegin(); it != projectiles.cend();) {
    if (it->second->alive == false) {
      int x_pos = it->second->x_position;
      int y_pos = it->second->y_position;
      map->empty_cell(x_pos, y_pos);
      delete it->second;
      it = projectiles.erase(it++);
    } else {
      ++it;
    }
  }
}