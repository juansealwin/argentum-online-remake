#include "monsters_factory.h"

Monster* MonstersFactory::create_random_monster(Json::Value& monsters_cfg,
                                                unsigned int& entities_ids,
                                                Map& map) {

  int random_int =
      HelperFunctions::random_int(first_monster_id, last_monster_id);
  Json::Value monster_cfg = Json::arrayValue;
  switch (random_int) {
    case zombie:
      monster_cfg = monsters_cfg["zombie"];
      break;
    case spider:
      monster_cfg = monsters_cfg["spider"];
      break;
    case goblin:
      monster_cfg = monsters_cfg["goblin"];
      break;
    case skeleton:
      monster_cfg = monsters_cfg["skeleton"];
      break;
  }

  std::tuple<int, int> coordinates = map.get_random_free_unsafe_space();
  int x = std::get<0>(coordinates);
  int y = std::get<1>(coordinates);
  Monster* m =
      new Monster(entities_ids, x, y, monster_cfg["id"].asInt(), 'g',
                  monster_cfg["maxHp"].asInt(), monster_cfg["level"].asInt(),
                  monster_cfg["dps"].asInt(), map);
  map.ocupy_cell(x, y, entities_ids);
  return m;
}