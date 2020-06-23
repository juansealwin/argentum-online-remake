#ifndef DEFENSIVE_ITEM_H
#define DEFENSIVE_ITEM_H
#include "item.h"

class DefensiveItem : public Item {
 public:
  DefensiveItem(int id, unsigned int min_defense, unsigned int max_defense);
  virtual ~DefensiveItem();
  DefensiveItem(const DefensiveItem &) = delete;
  unsigned int min_defense, max_defense;
};
#endif  // DEFENSIVE_ITEM_H
