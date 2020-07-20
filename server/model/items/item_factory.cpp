#include "item_factory.h"

#include "item_ids.h"
Item *ItemFactory::create_random_item(Json::Value &items_config) {
  int random_id = HelperFunctions::random_int(first_item_id, last_item_id);
  return create_item(items_config, (item_t)random_id);
}

Item* ItemFactory::create_item(Json::Value &items_config, item_t item) {
switch (item) {
    case turtle_shield:
      return create_turtle_shield(items_config);
    case iron_shield:
      return create_iron_shield(items_config);
    case hood:
      return create_hood(items_config);
    case iron_helmet:
      return create_iron_helmet(items_config);
    case magic_hat:
      return create_magic_hat(items_config);
    case leather_armour:
      return create_leather_armour(items_config);
    case plate_armour:
      return create_plate_armour(items_config);
    case blue_tunic:
      return create_blue_tunic(items_config);
    case hp_potion:
      return create_hp_potion(items_config);
    case mana_potion:
      return create_mana_potion(items_config);
    case sword:
      return create_sword(items_config);
    case axe:
      return create_axe(items_config);
    case hammer:
      return create_hammer(items_config);
    case simple_bow:
      return create_simple_bow(items_config);
    case compound_bow:
      return create_compound_bow(items_config);
    case ash_stick:
      return create_ash_stick(items_config);
    case gnarled_staff:
      return create_gnarled_staff(items_config);
    case crimp_staff:
      return create_crimp_staff(items_config);
    case elven_flute:
      return create_elven_flute(items_config);
    case deadly_staff:
      return create_deadly_staff(items_config);
    default:
      return nullptr;
  }
}

unsigned int ItemFactory::get_item_price(Json::Value &items_config, item_t item) {
  Json::Value cfg;
  switch (item) {
    case turtle_shield:
      cfg = items_config["defense"]["shields"]["turtleShield"];
      break;
    case iron_shield:
      cfg = items_config["defense"]["shields"]["ironShield"];
      break;
    case hood:
      cfg = items_config["defense"]["helmets"]["hood"];
      break;
    case iron_helmet:
      cfg = items_config["defense"]["helmets"]["ironHelmet"];
      break;
    case magic_hat:
      cfg = items_config["defense"]["helmets"]["magicHat"];
      break;
    case leather_armour:
      cfg = items_config["defense"]["armour"]["leatherArmour"];
      break;
    case plate_armour:
      cfg = items_config["defense"]["armour"]["plateArmour"];
      break;
    case blue_tunic:
      cfg = items_config["defense"]["armour"]["blueTunic"];
      break;
    case hp_potion:
      cfg = items_config["consumables"]["hpPotion"];
      break;
    case mana_potion:
      cfg = items_config["consumables"]["manaPotion"];
      break;
    case sword:
      cfg = items_config["weapons"]["sword"];
      break;
    case axe:
      cfg = items_config["weapons"]["axe"];
      break;
    case hammer:
      cfg = items_config["weapons"]["hammer"];
      break;
    case simple_bow:
      cfg = items_config["weapons"]["simpleBow"];
      break;
    case compound_bow:
      cfg = items_config["weapons"]["compoundBow"];
      break;
    case ash_stick:
      cfg = items_config["staffs"]["ashStick"];
      break;
    case gnarled_staff:
      cfg = items_config["staffs"]["gnarledStaff"];
      break;
    case crimp_staff:
      cfg = items_config["staffs"]["crimpStaff"];
      break;
    case elven_flute:
      cfg = items_config["staffs"]["elvenFlute"];
      break;
    default:
      return 0;
  }
  return cfg["price"].asUInt();
}

DefensiveItem *ItemFactory::create_turtle_shield(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["shields"]["turtleShield"];
  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
DefensiveItem *ItemFactory::create_iron_shield(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["shields"]["ironShield"];
  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
DefensiveItem *ItemFactory::create_hood(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["helmets"]["hood"];

  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
DefensiveItem *ItemFactory::create_iron_helmet(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["helmets"]["ironHelmet"];

  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}

DefensiveItem *ItemFactory::create_magic_hat(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["helmets"]["magicHat"];

  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
DefensiveItem *ItemFactory::create_leather_armour(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["armour"]["leatherArmour"];

  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
DefensiveItem *ItemFactory::create_plate_armour(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["armour"]["plateArmour"];

  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
DefensiveItem *ItemFactory::create_blue_tunic(Json::Value &items_config) {
  Json::Value cfg = items_config["defense"]["armour"]["blueTunic"];

  return new DefensiveItem(cfg["id"].asUInt(), cfg["min_defense"].asUInt(),
                           cfg["max_defense"].asUInt());
}
Consumable *ItemFactory::create_hp_potion(Json::Value &items_config) {
  Json::Value cfg = items_config["consumables"]["hpPotion"];
  return new Consumable(cfg["id"].asUInt(), cfg["manaRegen"].asUInt(),
                        cfg["hpRegen"].asUInt());
}
Consumable *ItemFactory::create_mana_potion(Json::Value &items_config) {
  Json::Value cfg = items_config["consumables"]["manaPotion"];
  return new Consumable(cfg["id"].asUInt(), cfg["manaRegen"].asUInt(),
                        cfg["hpRegen"].asUInt());
}
Weapon *ItemFactory::create_sword(Json::Value &items_config) {
  Json::Value cfg = items_config["weapons"]["sword"];
  return new Weapon(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                    cfg["maxDmg"].asUInt(), cfg["range"].asUInt());
}
Weapon *ItemFactory::create_axe(Json::Value &items_config) {
  Json::Value cfg = items_config["weapons"]["axe"];
  return new Weapon(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                    cfg["maxDmg"].asUInt(), cfg["range"].asUInt());
}
Weapon *ItemFactory::create_hammer(Json::Value &items_config) {
  Json::Value cfg = items_config["weapons"]["hammer"];
  return new Weapon(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                    cfg["maxDmg"].asUInt(), cfg["range"].asUInt());
}
Weapon *ItemFactory::create_simple_bow(Json::Value &items_config) {
  Json::Value cfg = items_config["weapons"]["simpleBow"];
  return new Weapon(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                    cfg["maxDmg"].asUInt(), cfg["range"].asUInt());
}
Weapon *ItemFactory::create_compound_bow(Json::Value &items_config) {
  Json::Value cfg = items_config["weapons"]["compoundBow"];
  return new Weapon(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                    cfg["maxDmg"].asUInt(), cfg["range"].asUInt());
}
Staff *ItemFactory::create_ash_stick(Json::Value &items_config) {
  Json::Value cfg = items_config["staffs"]["ashStick"];
  return new Staff(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                   cfg["maxDmg"].asUInt(), cfg["range"].asUInt(),
                   cfg["mana"].asUInt(), cfg["hpRecovery"].asUInt());
}
Staff *ItemFactory::create_gnarled_staff(Json::Value &items_config) {
  Json::Value cfg = items_config["staffs"]["gnarledStaff"];
  return new Staff(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                   cfg["maxDmg"].asUInt(), cfg["range"].asUInt(),
                   cfg["mana"].asUInt(), cfg["hpRecovery"].asUInt());
}
Staff *ItemFactory::create_crimp_staff(Json::Value &items_config) {
  Json::Value cfg = items_config["staffs"]["crimpStaff"];
  return new Staff(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                   cfg["maxDmg"].asUInt(), cfg["range"].asUInt(),
                   cfg["mana"].asUInt(), cfg["hpRecovery"].asUInt());
}
Staff *ItemFactory::create_elven_flute(Json::Value &items_config) {
  Json::Value cfg = items_config["staffs"]["elvenFlute"];
  return new Staff(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                   cfg["maxDmg"].asUInt(), cfg["range"].asUInt(),
                   cfg["mana"].asUInt(), cfg["hpRecovery"].asUInt());
}

Staff *ItemFactory::create_deadly_staff(Json::Value &items_config) {
  Json::Value cfg = items_config["staffs"]["deadlyStaff"];
  return new Staff(cfg["id"].asUInt(), cfg["minDmg"].asUInt(),
                   cfg["maxDmg"].asUInt(), cfg["range"].asUInt(),
                   cfg["mana"].asUInt(), cfg["hpRecovery"].asUInt());
}