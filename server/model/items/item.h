#ifndef ITEM_H
#define ITEM_H
#include "hero.h"
class Hero;
class Item {
 public:
  Item(unsigned int id);
  virtual bool can_be_used_by(Hero &hero);
  virtual void use(Hero &hero);
  virtual ~Item();
  Item(const Item &) = delete;
  int id;
};
#endif  // ITEM_H
