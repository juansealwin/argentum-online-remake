#include "defensive_item.h"

#include "item.h"

DefensiveItem::DefensiveItem(int id, unsigned int min_defense,
                             unsigned int max_defense)
    : Item(id), min_defense(min_defense), max_defense(max_defense) {}

DefensiveItem::~DefensiveItem() {}

void DefensiveItem::use(Hero *hero) {
  switch (this->id) {
    case turtle_shield:
      equip_on_shield_slot(hero);
      break;
    case iron_shield:
      equip_on_shield_slot(hero);
      break;
    case hood:
      equip_on_helmet_slot(hero);

      break;
    case iron_helmet:
      equip_on_helmet_slot(hero);

      break;
    case magic_hat:
      equip_on_helmet_slot(hero);

      break;
    case leather_armour:
      equip_on_armour_slot(hero);
      break;
    case plate_armour:
      equip_on_armour_slot(hero);

      break;
    case blue_tunic:
      equip_on_armour_slot(hero);

      break;
  }
}
/******************** metodos privados *******************************/

void DefensiveItem::equip_on_shield_slot(Hero *hero) {
  DefensiveItem *i = hero->equipment->unequip_shield();
  // hero->unequip_shield();
  hero->equip_shield(this->id);
  if (i) hero->add_item(i);
}
void DefensiveItem::equip_on_helmet_slot(Hero *hero) {
  DefensiveItem *i = hero->equipment->unequip_helmet();

  // hero->unequip_helmet();
  hero->equip_helmet(this->id);
  if (i) hero->add_item(i);
}
void DefensiveItem::equip_on_armour_slot(Hero *hero) {
  DefensiveItem *i = hero->equipment->unequip_armour();
  // hero->unequip_armour();
  hero->equip_armour(this->id);
  if (i) hero->add_item(i);
}