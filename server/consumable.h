#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"
class Consumable : Item {
 public:
  Consumable(int id, unsigned int mana_regen, unsigned int hp_regen);
  virtual bool can_be_used_by(Hero &hero);
  virtual ~Consumable();
  Consumable(const Consumable &) = delete;
  virtual void self_apply(Hero &hero);
  unsigned int mana_regen, hp_regen, range;
};
#endif  // CONSUMABLE_H
