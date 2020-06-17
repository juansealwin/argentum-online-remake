#include "stdint.h"
#ifndef MONSTER_H
#define MONSTER_H
#include <vector>

#include "base_character.h"
class Monster : public BaseCharacter {
 public:
  Monster(int x, int y, int id, char repr, int hp, int level, int dps,
          Map *map);
  Monster(const Monster &) = delete;
  bool is_movable() override;
  void update() override;
  virtual ~Monster();

 private:
  int dps;
  std::vector<std::tuple<int, int>> moves;
  std::size_t current_move = 0;
};

#endif  // MONSTER_H
