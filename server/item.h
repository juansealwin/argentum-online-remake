#ifndef ITEM_H
#define ITEM_H
#include "hero.h"
class Item {
 public:
  Item(int id);
  virtual bool can_be_used_by(Hero &hero);
  virtual void self_apply(Hero &hero);
  virtual ~Item();
  Item(const Item &) = delete;
 protected:
  int id;
};
#endif  // ITEM_H
