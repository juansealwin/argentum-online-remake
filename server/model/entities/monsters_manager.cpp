#include "monsters_manager.h"

#include "hero.h"
MonstersManager::MonstersManager() {
  last_update_time = std::chrono::high_resolution_clock::now();
}

MonstersManager::~MonstersManager() {}

void MonstersManager::update(std::map<unsigned int, Monster *> &monsters,
                             std::map<unsigned int, Hero *> heroes,
                             MessageCenter &message_center) {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_update_time;

  for (auto &monster : monsters) {
    bool attacked_or_moved_to_hero = false;
    if (time_difference.count() >= 800000000) {
      last_update_time = actual_time;
      for (auto &hero : heroes) {
        if (!hero.second->is_death()) {
          attacked_or_moved_to_hero = attack_or_move_to_hero(monster.second, hero.second,
                                      message_center);
          if (attacked_or_moved_to_hero) break;
        }
      }
      if(!attacked_or_moved_to_hero) monster.second->auto_move();
    }
    monster.second->clear_effects();
  }
}

bool MonstersManager::attack_or_move_to_hero(Monster *m, Hero *h,
                                             MessageCenter &message_center) {
  if (m->is_next_to(h->x_position, h->y_position)) {
    const Attack att = m->attack();
    unsigned int dmg =
        h->receive_damage(att.damage, att.critical, att.attacker_weapon_id);
    //std::cout << "@@@@dmg returned from h->receive damage: @@@" << std::endl;
    message_center.notify_damage_received(h->get_name(), dmg, m->get_name());
    // atacar
    return true;
  } else if (m->is_close_to(h->x_position, h->y_position)) {
    m->move_closer_to(h->x_position, h->y_position);
    return true;
  }
  return false;
}

void MonstersManager::remove_death_monsters(
    std::map<unsigned int, Monster *> &monsters, Map *map) {
  for (auto it = monsters.cbegin(); it != monsters.cend();) {
    if (it->second->alive == false) {
      int x_pos = it->second->x_position;
      int y_pos = it->second->y_position;
      map->empty_cell(x_pos, y_pos);
      delete it->second;
      it = monsters.erase(it++);
    } else {
      ++it;
    }
  }
}

void MonstersManager::respawn_monsters(
    std::map<unsigned int, Monster *> &monsters, Map *map,
    unsigned int total_monster_poblation, Json::Value &monsters_cfg,
    unsigned int &entities_ids) {
  while (monsters.size() < total_monster_poblation) {
    Monster *random_monster =
        MonstersFactory::create_random_monster(monsters_cfg, entities_ids, map);
    monsters.emplace(entities_ids++, random_monster);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
