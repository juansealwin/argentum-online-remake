#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H
#include "item.h"
#include "defensive_item.h"
#include "weapon.h"
#include "staff.h"
#include "consumable.h"
#include "helper_functions.h"

// #include <random>
// #include <chrono>

namespace ItemFactory {
  Item* create_random_item(Json::Value items_config);
  DefensiveItem* create_turtle_shield(Json::Value items_config);
  DefensiveItem* create_iron_shield(Json::Value items_config);
  DefensiveItem* create_hood(Json::Value items_config);
  DefensiveItem* create_iron_helmet(Json::Value items_config);
  DefensiveItem* create_magic_hat(Json::Value items_config);
  DefensiveItem* create_leather_armour(Json::Value items_config);
  DefensiveItem* create_plate_armour(Json::Value items_config);
  DefensiveItem* create_blue_tunic(Json::Value items_config);
  Consumable* create_hp_potion(Json::Value items_config);
  Consumable* create_mana_potion(Json::Value items_config);
  Weapon* create_sword(Json::Value items_config);
  Weapon* create_axe(Json::Value items_config);
  Weapon* create_hammer(Json::Value items_config);
  Weapon* create_simple_bow(Json::Value items_config);
  Weapon* create_compound_bow(Json::Value items_config);
  Staff* create_ash_stick(Json::Value items_config);
  Staff* create_gnarled_staff(Json::Value items_config);
  Staff* create_crimp_staff(Json::Value items_config);
  Staff* create_elven_flute(Json::Value items_config);
}
#endif  // ITEM_FACTORY_H
