#include "serializer.h"

#include "defensive_item.h"
#include "staff.h"

template <typename T>
// debe llamarse a este metodo si se necesita extraer del vector elementos de
// mas de 1 byte
T extract(const std::vector<unsigned char> &v, unsigned int &pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  pos += sizeof(T);
  return value;
}

template <typename X>
// debe llamarse a este metodo si se necesita insertar en el vector elementos de
// mas de 1 byte
void insert(std::vector<unsigned char> &v, X value) {
  unsigned int current_pos = v.size();
  v.resize(v.size() + sizeof(X));
  memcpy(v.data() + current_pos, &value, sizeof(X));
}

void Serializer::serialize_common_fields(
    std::vector<unsigned char> &serialization, uint16_t uid, Entity *entity) {
  // std::cout << "uid to serialize: " << uid << std::endl;
  uint16_t entity_id = htons(uid);
  insert(serialization, entity_id);
  uint8_t entity_type = entity->type;
  uint8_t x = entity->x_position;
  uint8_t y = entity->y_position;
  uint8_t orientation = entity->orientation;
  serialization.push_back(entity_type);
  serialization.push_back(x);
  serialization.push_back(y);
  serialization.push_back(orientation);
}

std::vector<unsigned char> Serializer::serialize_game_status(
    ArgentumGame *game) {
  std::vector<unsigned char> serialization;
  // mover a la clase
  // unsigned int monsters_serialized = 0;
  uint8_t notification_id = 1;
  serialization.push_back(notification_id);
  // std::cout << "@@@@@@@@@monsters size is@@@@@@@@@@ " <<
  // game->monsters.size() << std::endl;
  for (auto &entity : game->npcs) {
    serialize_common_fields(std::ref(serialization), entity.first,
                            entity.second);
  }
  for (auto &entity : game->heroes) {
    serialize_common_fields(std::ref(serialization), entity.first,
                            entity.second);
    serialize_hero(std::ref(serialization), entity.second, true);
    // std::cout << "serialized hero, his id is " << entity.second->unique_id <<
    // std::endl;
  }
  for (auto &entity : game->monsters) {
    // monsters_serialized++;
    serialize_common_fields(std::ref(serialization), entity.first,
                            entity.second);
    serialize_monster(std::ref(serialization), entity.second);
  }

  // for (auto &entity : game->projectiles) {
  //   serialize_common_fields_v2(std::ref(serialization), entity.first,
  //                              entity.second);
  // }
  for (std::pair<std::tuple<unsigned int, unsigned int>, Drop *> element :
       game->drops) {
    // Accessing KEY from element
    std::tuple<unsigned int, unsigned int> coordinates = element.first;
    Drop *drop = element.second;
    serialize_drop(serialization, drop, coordinates);
  }
  // debug_deserialize_v3(serialization);
  return serialization;
}

void Serializer::serialize_drop(
    std::vector<unsigned char> &serialization, Drop *drop,
    std::tuple<unsigned int, unsigned int> coordinates) {
  uint16_t entity_id = htons(drop->unique_id);
  insert(serialization, entity_id);
  uint8_t entity_type = drop->id;
  uint8_t x = std::get<0>(coordinates);
  uint8_t y = std::get<1>(coordinates);
  uint8_t orientation = 3;
  serialization.push_back(entity_type);
  serialization.push_back(x);
  serialization.push_back(y);
  serialization.push_back(orientation);
  std::vector<Item *> items = drop->items;
  uint8_t items_in_drop = items.size();
  if (drop->ammount_of_gold() > 0) items_in_drop++;
  serialization.push_back(items_in_drop);
  if (drop->ammount_of_gold() > 0) {
    serialization.push_back(GOLD_ID);
  }
  for (unsigned int i = 0; i < items.size(); i++) {
    uint8_t item_id = items.at(i)->id;
    serialization.push_back(item_id);
  }
}

void Serializer::serialize_monster(std::vector<unsigned char> &serialization,
                                   Monster *m) {
  uint16_t max_hp = htons(m->max_hp);
  uint16_t current_hp = htons(m->current_hp);
  uint16_t level = htons(m->level);
  uint8_t affected_by_item = m->affected_by;
  insert(serialization, max_hp);
  insert(serialization, current_hp);
  insert(serialization, level);
  insert(serialization, affected_by_item);
}

void Serializer::serialize_hero(std::vector<unsigned char> &serialization,
                                Hero *h, const bool use_htons) {
  /************** serializacion del estado del heroe ***************/
  uint16_t max_hp = use_htons ? htons(h->max_hp) : h->max_hp;
  uint16_t current_hp = use_htons ? htons(h->current_hp) : h->current_hp;
  uint16_t level = use_htons ? htons(h->level) : h->level;
  uint8_t affected_by_item = h->affected_by;
  uint8_t name_size = h->name.size();
  uint8_t class_id = h->class_id;
  uint16_t mana_max = use_htons ? htons(h->max_mana) : h->max_mana;
  uint16_t curr_mana = use_htons ? htons(h->current_mana) : h->current_mana;
  uint16_t str = use_htons ? htons(h->strength) : h->strength;
  uint16_t intelligence = use_htons ? htons(h->intelligence) : h->intelligence;
  uint16_t agility = use_htons ? htons(h->agility) : h->agility;
  uint16_t constitution = use_htons ? htons(h->constitution) : h->constitution;
  uint16_t gold = use_htons ? htons(h->inventory->current_gold())
                            : h->inventory->current_gold();
  uint16_t xp_limit =
      use_htons ? htons(h->next_level_xp_limit) : h->next_level_xp_limit;
  uint16_t current_xp = use_htons ? htons(h->experience) : h->experience;
  uint8_t meditating = (int)h->meditating;
  uint8_t ghost_mode = (int)h->ghost_mode;
  uint8_t close_to_npc = (int)h->close_to_npc;

  insert(serialization, max_hp);
  insert(serialization, current_hp);
  insert(serialization, level);
  insert(serialization, affected_by_item);
  serialization.push_back(name_size);
  for (int x = 0; x < name_size; x++) {
    serialization.push_back(h->name.at(x));
  }
  serialization.push_back(class_id);
  insert(serialization, mana_max);
  insert(serialization, curr_mana);
  insert(serialization, str);
  insert(serialization, intelligence);
  insert(serialization, agility);
  insert(serialization, constitution);
  insert(serialization, gold);
  insert(serialization, xp_limit);
  insert(serialization, current_xp);
  serialization.push_back(meditating);
  serialization.push_back(ghost_mode);
  serialization.push_back(close_to_npc);
  /*********** serializacion del equipamiento **********/
  uint8_t items_equiped = h->equipment->count();
  serialization.push_back(items_equiped);
  if (items_equiped > 0) {
    if (h->equipment->helmet != nullptr) {
      serialization.push_back(0);  // slot de casco
      uint8_t helmet_id = h->equipment->helmet->id;
      serialization.push_back(helmet_id);
    }
    if (h->equipment->armour != nullptr) {
      serialization.push_back(1);  // slot de armadura
      uint8_t armour_id = h->equipment->armour->id;
      serialization.push_back(armour_id);
    }
    if (h->equipment->shield != nullptr) {
      serialization.push_back(2);  // slot de escudo
      uint8_t shield_id = h->equipment->shield->id;
      serialization.push_back(shield_id);
    }
    if (h->equipment->staff != nullptr) {
      serialization.push_back(3);  // slot de vara
      uint8_t staff_id = h->equipment->staff->id;
      serialization.push_back(staff_id);
    }
    if (h->equipment->weapon != nullptr) {
      serialization.push_back(4);  // slot de arma
      uint8_t weapon_id = h->equipment->weapon->id;
      serialization.push_back(weapon_id);
    }
  }
  /******************** serializacion inventario **********************/
  uint8_t items_inventory = h->inventory->items.size();
  serialization.push_back(items_inventory);
  std::vector<Item *> items = h->inventory->items;
  for (int i = 0; i < items_inventory; i++) {
    uint8_t item_id = items.at(i)->id;
    serialization.push_back(item_id);
  }
}

void Serializer::serialize_bank_of_hero(
    std::vector<unsigned char> &serialization, Hero *h) {
  std::vector<Item *> items = h->bank->items;
  uint8_t bank_size = items.size();
  serialization.push_back(bank_size);
  for (unsigned int i = 0; i < items.size(); i++) {
    uint8_t item_id = items.at(i)->id;
    serialization.push_back(item_id);
  }
  uint16_t gold = h->bank->current_gold();
  unsigned int current_pos = serialization.size();
  serialization.resize(serialization.size() + sizeof(gold));
  memcpy(serialization.data() + current_pos, &gold, sizeof(gold));
}

// void Serializer::debug_deserialize_v3(
//     std::vector<unsigned char> serialization) {
//   unsigned int monsters_detected, entities_quantity = 0;
//   unsigned int heroes_detected = 0;
//   unsigned int npcs_or_others_detected = 0;
//   unsigned int drops_detected = 0;
//   unsigned int j = 1;
//   while (j < serialization.size()) {
//     uint16_t id = ntohs(extract<uint16_t>(serialization, j));
//     int entity_type = extract<uint8_t>(serialization, j);
//     entities_quantity++;
//     int x = extract<uint8_t>(serialization, j);
//     int y = extract<uint8_t>(serialization, j);
//     int orientation = extract<uint8_t>(serialization, j);
//     // std::cout << "Entity id: " << id << ", type: " << entity_type
//     //           << ", x_pos: " << x << ", y_pos: " << y
//     //           << "orientation: " << orientation << std::endl;
//     if (is_drop(entity_type)) {
//       drops_detected++;
//       int items_in_drop = extract<uint8_t>(serialization, j);
//       for (int x = items_in_drop; x > 0; x--) {
//         int current_item_id = extract<uint8_t>(serialization, j);
//         // std::cout << "dropped item " << current_item_id << std::endl;
//       }
//       // int drop_has_coins = extract<uint8_t>(serialization, j);
//       // if (drop_has_coins == 1) {
//       //   // std::cout << "Drop has coins!!" << std::endl;
//       // }
//     }
//     if (is_monster(entity_type)) {
//       monsters_detected++;
//       // std::cout << "deserialized a monster with id " << id << std::endl;
//       uint16_t max_hp = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t current_hp = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t level = ntohs(extract<uint16_t>(serialization, j));
//       uint8_t affected_by = extract<uint8_t>(serialization, j);
//       // if (affected_by != 0) {
//       //   std::cout << "monster affected by : " << (int)affected_by <<
//       //   std::endl;
//       // }
//       // std::cout << "Monster: lvl: " << level << "maxhp: " << max_hp
//       //           << "current_hp" << current_hp << std::endl;
//     } else if (is_hero(entity_type)) {
//       heroes_detected++;
//       // std::cout << "deserialized a hero with id " << id << std::endl;
//       uint16_t max_hp = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t current_hp = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t level = ntohs(extract<uint16_t>(serialization, j));
//       uint8_t affected_by = extract<uint8_t>(serialization, j);
//       // if (affected_by != 0) {
//       //   std::cout << "hero affected by : " << (int)affected_by <<
//       std::endl;
//       // }
//       int name_size = extract<uint8_t>(serialization, j);
//       std::string name;
//       for (int x = 0; x < name_size; x++) {
//         name += serialization.at(j);
//         j++;
//       }
//       // std::cout << "Name of the hero: " << name << "id of the hero " <<
//       id<<
//       // std::endl;
//       int class_id = extract<uint8_t>(serialization, j);
//       uint16_t mana_max = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t curr_mana = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t str = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t intelligence = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t agility = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t constitution = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t gold = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t xp_limit = ntohs(extract<uint16_t>(serialization, j));
//       uint16_t current_xp = ntohs(extract<uint16_t>(serialization, j));
//       int meditating = extract<uint8_t>(serialization, j);
//       // std::cout << "meditating? " << meditating << std::endl;
//       int ghost_mode = extract<uint8_t>(serialization, j);
//       int close_to_npc = extract<uint8_t>(serialization, j);
//       int items_equiped = extract<uint8_t>(serialization, j);
//       // std::cout << "@@@Hero stats@@@" << std::endl
//       //           << "max_hp: " << max_hp << " max_mana " << mana_max << "
//       //           gold"
//       //           << gold << " ghost mode " << ghost_mode << " items equiped
//       "
//       //           << items_equiped << "name size" << name_size << std::endl;
//       // std::cout << "@@Deserializing items equiped@@" << std::endl;
//       for (int x = items_equiped; x > 0; x--) {
//         int current_item_slot = extract<uint8_t>(serialization, j);
//         int current_item_id = extract<uint8_t>(serialization, j);
//         // std::cout << "equiped " << current_item_id << " at "
//         //           << current_item_slot << std::endl;
//       }

//       int items_inventory = extract<uint8_t>(serialization, j);
//       // std::cout << "items in inventory: " << items_inventory << std::endl;
//       // std::cout << "@@Deserializing items in invetory@@" << std::endl;
//       for (int x = items_inventory; x > 0; x--) {
//         int inventory_item_id = extract<uint8_t>(serialization, j);
//         // std::cout << "item in inventory " << inventory_item_id <<
//         std::endl;
//       }
//     } else {
//       npcs_or_others_detected++;
//       // std::cout << "deserialized a ???? with id " << id << std::endl;
//       // Deberia ser un NPC, no tiene mas atributos
//     }
//   }
//   // std::cout << "Enviando: " << entities_quantity << " entidades" <<
//   // std::endl;
//   // std::cout << "monsters detecteD: " << monsters_detected << "
//   // heroes_detected " << heroes_detected << " npcs_or_others_detected " <<
//   // npcs_or_others_detected << " drops detected " << drops_detected <<
//   // std::endl;
// }

/************* METODOS PRIVADOS **************/

bool Serializer::vector_contains(std::vector<uint8_t> v, uint8_t x) {
  if (std::find(v.begin(), v.end(), x) != v.end()) return true;
  return false;
}

bool Serializer::is_hero(uint8_t t) {
  const std::vector<uint8_t> heroes = {25, 26, 27, 28};
  return vector_contains(heroes, t);
}

bool Serializer::is_monster(uint8_t t) {
  const std::vector<uint8_t> monsters = {29, 30, 31, 32};
  return vector_contains(monsters, t);
}

bool Serializer::is_drop(uint8_t t) { return (t == 37); }

Hero *Serializer::deserialize_hero(std::vector<unsigned char> &serialization,
                                   Json::Value &entities_cfg, int id, int x,
                                   int y, Map *map) {
  int class_id, affected_by, meditating, ghost_mode, close_to_npc,
      items_equiped, items_inventory;
  uint16_t max_hp, current_hp, level, mana_max, curr_mana, str, intelligence,
      agility, constitution, gold, xp_limit, current_xp;

  unsigned int j = 0;
  int entity_type = extract<uint8_t>(serialization, j);
  std::cout << "entity type: " << entity_type << std::endl;

  max_hp = extract<uint16_t>(serialization, j);  // no se usa aun
  current_hp = extract<uint16_t>(serialization, j);
  level = extract<uint16_t>(serialization, j);
  affected_by = extract<uint8_t>(serialization, j);  // no se usa aun
  std::cout << "lvl: " << level << " maxhp: " << max_hp << " current_hp "
            << current_hp << std::endl;

  uint8_t name_size = extract<uint8_t>(serialization, j);
  std::string name;
  for (int x = 0; x < name_size; x++) {
    name += serialization.at(j);
    j++;
  }
  std::cout << "nombre desearilizado: " << name << std::endl;
  class_id = extract<uint8_t>(serialization, j);
  mana_max = (extract<uint16_t>(serialization, j));  // no se usa aun
  curr_mana = (extract<uint16_t>(serialization, j));
  str = (extract<uint16_t>(serialization, j));
  intelligence = (extract<uint16_t>(serialization, j));
  agility = (extract<uint16_t>(serialization, j));
  constitution = (extract<uint16_t>(serialization, j));
  gold = (extract<uint16_t>(serialization, j));
  xp_limit = (extract<uint16_t>(serialization, j));
  current_xp = (extract<uint16_t>(serialization, j));
  meditating = extract<uint8_t>(serialization, j);  // no se usa aun
  ghost_mode = extract<uint8_t>(serialization, j);
  close_to_npc = extract<uint8_t>(serialization, j);  // no se usa aun
  std::cout << "@@@Hero stats@@@" << std::endl
            << "max_hp: " << max_hp << " max_mana " << mana_max << " gold "
            << gold << " ghost mode " << ghost_mode << std::endl;

  const std::string race_name =
      entities_cfg["idToRace"][std::to_string(entity_type)].asString();
  Json::Value race_stats = entities_cfg["races"][race_name];

  const std::string class_name =
      entities_cfg["idToClass"][std::to_string(class_id)].asString();
  Json::Value class_stats = entities_cfg["classes"][class_name];

  Hero *hero = new Hero(
      id, x, y, race_stats["id"].asUInt(), 'h', level, str, intelligence,
      agility, constitution, class_stats["fClassHp"].asUInt(),
      race_stats["fRaceHp"].asUInt(), race_stats["fRaceRecovery"].asUInt(),
      race_stats["fRaceMana"].asUInt(), class_stats["fClassMana"].asUInt(),
      class_stats["fClassMeditation"].asUInt(), gold, class_id, map, name,
      entities_cfg["criticalDamageMultiplier"].asFloat(),
      entities_cfg["inventorySize"].asInt(),
      entities_cfg["criticalDamageProbability"].asFloat(),
      entities_cfg["evasionProbability"].asFloat(),
      entities_cfg["maxSafeGoldMultiplier"].asFloat(),
      entities_cfg["levelUpLimitPower"].asFloat(),
      entities_cfg["startingXpCap"].asFloat(), entities_cfg["bankSize"].asInt(),
      entities_cfg["amountOfExperienceToUpdate"].asUInt(), false);

  hero->set_hp(current_hp);
  hero->set_mana(curr_mana);
  hero->set_ghost_mode(false);
  hero->set_next_level_xp_limit(xp_limit);
  hero->set_experience(current_xp);

  // Agregamos los items equipados
  items_equiped = extract<uint8_t>(serialization, j);
  for (int x = items_equiped; x > 0; x--) {
    int current_item_slot = extract<uint8_t>(serialization, j);
    int current_item_id = extract<uint8_t>(serialization, j);

    Item *i = ItemFactory::create_item(entities_cfg["items"],
                                       (item_t)current_item_id);
    hero->add_item(i);
    switch (current_item_slot) {
      case 0:  // slot de casco
        hero->equip_helmet(current_item_id);
        break;
      case 1:  // slot de armadura
        hero->equip_armour(current_item_id);
        break;
      case 2:  // slot de escudo
        hero->equip_shield(current_item_id);
        break;
      case 3:  // slot de vara
        hero->equip_staff(current_item_id);
        break;
      case 4:  // slot de arma
        hero->equip_weapon(current_item_id);
        break;
      default:
        break;
    }
  }

  // Agregamos los items del inventario
  items_inventory = extract<uint8_t>(serialization, j);
  std::cout << "items in inventory: " << items_inventory << std::endl;
  for (int x = items_inventory; x > 0; x--) {
    int current_item_id = extract<uint8_t>(serialization, j);
    Item *i = ItemFactory::create_item(entities_cfg["items"],
                                       (item_t)current_item_id);
    hero->add_item(i);
  }

  int bank_size = extract<uint8_t>(serialization, j);
  for (int x = 0; x < bank_size; x++) {
    int item = extract<uint8_t>(serialization, j);
    Item *i = ItemFactory::create_item(entities_cfg["items"], (item_t)item);
    hero->add_item_to_bank(i);
  }
  uint16_t gold_in_bank = extract<uint16_t>(serialization, j);
  hero->add_gold_to_bank(gold_in_bank);
  if (ghost_mode) {
    hero->set_ghost_mode(true);
  }
  return hero;
}
