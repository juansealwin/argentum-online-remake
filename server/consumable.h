#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"
class Consumable : Item {
 public:
  Consumable(int id, unsigned int mana_regen, unsigned int hp_regen);
  virtual ~Consumable();
  virtual void self_apply(Hero &hero);
  Consumable(const Consumable &) = delete;

  unsigned int mana_regen, hp_regen;
};
#endif  // CONSUMABLE_H
