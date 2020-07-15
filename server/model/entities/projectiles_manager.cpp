#include "projectiles_manager.h"

ProjectileManager::ProjectileManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

ProjectileManager::~ProjectileManager() {}

void ProjectileManager::update(
    std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters,
    std::map<unsigned int, Projectile *> &projectiles,
    MessageCenter &message_center, Json::Value &game_cfg) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;
  // 4 movimientos por segundo para los proyectiles
  if (time_difference.count() >= 93750000) {
    for (auto &projectile : projectiles) {
      Projectile *p = projectile.second;
      p->auto_move();
      if (p->collided) {
        manage_collision(p, heroes, monsters, message_center, game_cfg);
      }
    }
    last_update_time = actual_time;
  }
}

void ProjectileManager::manage_collision(
    Projectile *projectile, std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters, MessageCenter &message_center,
    Json::Value &game_cfg) {
  int attacked_id = projectile->get_collided_entity();

  unsigned int damage_done = 0;
  BaseCharacter *attacked, *attacker = nullptr;
  attacked = get_hero_or_monster(attacked_id, heroes, monsters);
  int attacker_id = projectile->get_attacker_id();
  attacker = get_hero_or_monster(attacker_id, heroes, monsters);
  // chequeo niveles
  unsigned int newbie_level_cap = game_cfg["newbieLevelCap"].asUInt();
  unsigned int pvp_level_diff_allowed =
      game_cfg["pvpLevelDifferenceAllowed"].asUInt();
  // std::cout << "afuera primer if" << std::endl;
  if (!attacker || !attacked) {
    projectile->kill();
    return;
  }
  if (dynamic_cast<Hero *>(attacker) && dynamic_cast<Hero *>(attacked)) {
    // std::cout << "adentro primer if" << std::endl;
    if ((HelperFunctions::difference(attacker->level, attacked->level) >=
         newbie_level_cap) ||
        attacked->level < pvp_level_diff_allowed) {
      // std::cout << "adentro if chequeo levels" << std::endl;

      message_center.notify_cant_attack_low_levels(
          attacker->get_name(), attacked->get_name(), attacked->level,
          newbie_level_cap);
      projectile->kill();
      return;
    }
  }
  // std::cout << "antes de if (attacked0" << std::endl;
  if (attacked) {
    // std::cout << "adentro if attacked chequeo levels" << std::endl;

    if (!attacked->is_death()) {
      // std::cout << "adentro if attacked !attackd is death" << std::endl;

      damage_done =
          attacked->receive_damage(projectile->get_damage(),
                                   projectile->is_critical(), projectile->type);
      if (attacker) {
        // std::cout << "adentro if attacker " << std::endl;

        attacker->notify_damage_done(attacked, damage_done);
      }
    }
  }
  // std::cout << "antes de if attacker" << std::endl;

  if (dynamic_cast<Hero *>(attacker)) {
    // std::cout << "dentro de if attacker" << std::endl;

    Hero *h = dynamic_cast<Hero *>(attacker);
    message_center.notify_damage_done(h->get_name(), damage_done,
                                      attacked->get_name());
  }
  if (dynamic_cast<Hero *>(attacked)) {
    // std::cout << "dentro de if attacked2" << std::endl;

    Hero *h = dynamic_cast<Hero *>(attacked);
    message_center.notify_damage_received(h->get_name(), damage_done,
                                          attacker->get_name());
  }
  // std::cout << "matando proyectil" << std::endl;
  projectile->kill();
}

BaseCharacter *ProjectileManager::get_hero_or_monster(
    int uid, std::map<unsigned int, Hero *> &heroes,
    std::map<unsigned int, Monster *> &monsters) {
  if (uid < 0) return nullptr;
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
      map->empty_projectile(x_pos, y_pos);
      delete it->second;
      it = projectiles.erase(it++);
    } else {
      ++it;
    }
  }
}