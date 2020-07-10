#ifndef MONSTERS_FACTORY_H
#define MONSTERS_FACTORY_H
#include "monster.h"
#include "helper_functions.h"

typedef enum {
  goblin = 29,
  spider,
  skeleton,
  zombie,
  first_monster_id = 29,
  last_monster_id = 32
} monster_t;

namespace MonstersFactory {
  Monster* create_random_monster(Json::Value &monsters_cfg, unsigned int &entities_ids, Map *map);
}
#endif  // MONSTERS_FACTORY_H
