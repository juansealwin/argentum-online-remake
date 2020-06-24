#ifndef CONSUMABLE_H
#define CONSUMABLE_H
#include "item.h"
class Consumable : public Item {
 public:
  Consumable(int id, unsigned int mana_regen, unsigned int hp_regen);
  virtual ~Consumable();
  virtual void use(Hero &hero) override;
  Consumable(const Consumable &) = delete;

  unsigned int mana_regen, hp_regen;
};
#endif  // CONSUMABLE_H
