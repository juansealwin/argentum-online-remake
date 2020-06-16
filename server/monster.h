#include "stdint.h"
#ifndef MONSTER_H
#define MONSTER_H
#include "base_character.h"
class Monster : public BaseCharacter {
 public:
  Monster(int x, int y, int id, char repr, int hp, int level, int dps);
  Monster(const Monster &) = delete;
  bool is_movable() override;
  virtual ~Monster();

 private:
  int dps;
};

#endif  // MONSTER_H
