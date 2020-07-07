#ifndef DEFENSIVE_ITEM_H
#define DEFENSIVE_ITEM_H
#include "item.h"
#include "item_ids.h"
class Item;
class DefensiveItem : public Item {
 public:
  DefensiveItem(int id, unsigned int min_defense, unsigned int max_defense);
  virtual ~DefensiveItem();
  DefensiveItem(const DefensiveItem &) = delete;
  unsigned int min_defense, max_defense;
  virtual void use(Hero *hero) override;
 private:
  void equip_on_shield_slot(Hero *hero);
  void equip_on_helmet_slot(Hero *hero);
  void equip_on_armour_slot(Hero *hero);

};
#endif  // DEFENSIVE_ITEM_H
