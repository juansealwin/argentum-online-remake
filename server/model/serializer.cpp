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

void Serializer::serialize_common_fields_v2(
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

std::vector<unsigned char> Serializer::serialize_game_status_v3(
    ArgentumGame *game) {
  std::vector<unsigned char> serialization;
  // mover a la clase
  unsigned int monsters_serialized = 0;
  uint8_t notification_id = 1;
  serialization.push_back(notification_id);
  // std::cout << "@@@@@@@@@monsters size is@@@@@@@@@@ " <<
  // game->monsters.size() << std::endl;
  for (auto &entity : game->npcs) {
    serialize_common_fields_v2(std::ref(serialization), entity.first,
                               entity.second);
  }
  for (auto &entity : game->heroes) {
    serialize_common_fields_v2(std::ref(serialization), entity.first,
                               entity.second);
    serialize_hero(std::ref(serialization), entity.second);
    // std::cout << "serialized hero, his id is " << entity.second->unique_id <<
    // std::endl;
  }
  for (auto &entity : game->monsters) {
    monsters_serialized++;
    serialize_common_fields_v2(std::ref(serialization), entity.first,
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
  debug_deserialize_v3(serialization);
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
  for (int i = 0; i < items.size(); i++) {
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
                                Hero *h) {
  /************** serializacion del estado del heroe ***************/
  uint16_t max_hp = htons(h->max_hp);
  uint16_t current_hp = htons(h->current_hp);
  uint16_t level = htons(h->level);
  uint8_t affected_by_item = h->affected_by;
  // aca meter el nombre
  uint8_t name_size = h->name.size();
  uint8_t class_id = h->class_id;
  uint16_t mana_max = htons(h->max_mana);
  uint16_t curr_mana = htons(h->current_mana);
  uint16_t str = htons(h->strength);
  uint16_t intelligence = htons(h->intelligence);
  uint16_t agility = htons(h->agility);
  uint16_t constitution = htons(h->constitution);
  uint16_t gold = htons(h->inventory->current_gold());
  uint16_t xp_limit = htons(h->next_level_xp_limit);
  uint16_t current_xp = htons(h->experience);
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

void Serializer::debug_deserialize_v3(
    std::vector<unsigned char> serialization) {
  unsigned int monsters_detected, entities_quantity = 0;
  unsigned int heroes_detected = 0;
  unsigned int npcs_or_others_detected = 0;
  unsigned int drops_detected = 0;
  unsigned int j = 1;
  while (j < serialization.size()) {
    uint16_t id = ntohs(extract<uint16_t>(serialization, j));
    int entity_type = extract<uint8_t>(serialization, j);
    entities_quantity++;
    int x = extract<uint8_t>(serialization, j);
    int y = extract<uint8_t>(serialization, j);
    int orientation = extract<uint8_t>(serialization, j);
    // std::cout << "Entity id: " << id << ", type: " << entity_type
    //           << ", x_pos: " << x << ", y_pos: " << y
    //           << "orientation: " << orientation << std::endl;
    if (is_drop(entity_type)) {
      drops_detected++;
      int items_in_drop = extract<uint8_t>(serialization, j);
      for (int x = items_in_drop; x > 0; x--) {
        int current_item_id = extract<uint8_t>(serialization, j);
        // std::cout << "dropped item " << current_item_id << std::endl;
      }
      // int drop_has_coins = extract<uint8_t>(serialization, j);
      // if (drop_has_coins == 1) {
      //   // std::cout << "Drop has coins!!" << std::endl;
      // }
    }
    if (is_monster(entity_type)) {
      monsters_detected++;
      // std::cout << "deserialized a monster with id " << id << std::endl;
      uint16_t max_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t current_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t level = ntohs(extract<uint16_t>(serialization, j));
      uint8_t affected_by = extract<uint8_t>(serialization, j);
      // if (affected_by != 0) {
      //   std::cout << "monster affected by : " << (int)affected_by << std::endl;
      // }
      // std::cout << "Monster: lvl: " << level << "maxhp: " << max_hp
      //           << "current_hp" << current_hp << std::endl;
    } else if (is_hero(entity_type)) {
      heroes_detected++;
      // std::cout << "deserialized a hero with id " << id << std::endl;
      uint16_t max_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t current_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t level = ntohs(extract<uint16_t>(serialization, j));
      uint8_t affected_by = extract<uint8_t>(serialization, j);
      // if (affected_by != 0) {
      //   std::cout << "hero affected by : " << (int)affected_by << std::endl;
      // }
      int name_size = extract<uint8_t>(serialization, j);
      std::string name;
      for (int x = 0; x < name_size; x++) {
        name += serialization.at(j);
        j++;
      }
      // std::cout << "Name of the hero: " << name << "id of the hero " << id<<
      // std::endl;
      int class_id = extract<uint8_t>(serialization, j);
      uint16_t mana_max = ntohs(extract<uint16_t>(serialization, j));
      uint16_t curr_mana = ntohs(extract<uint16_t>(serialization, j));
      uint16_t str = ntohs(extract<uint16_t>(serialization, j));
      uint16_t intelligence = ntohs(extract<uint16_t>(serialization, j));
      uint16_t agility = ntohs(extract<uint16_t>(serialization, j));
      uint16_t constitution = ntohs(extract<uint16_t>(serialization, j));
      uint16_t gold = ntohs(extract<uint16_t>(serialization, j));
      uint16_t xp_limit = ntohs(extract<uint16_t>(serialization, j));
      uint16_t current_xp = ntohs(extract<uint16_t>(serialization, j));
      int meditating = extract<uint8_t>(serialization, j);
      //std::cout << "meditating? " << meditating << std::endl;
      int ghost_mode = extract<uint8_t>(serialization, j);
      int close_to_npc = extract<uint8_t>(serialization, j);
      int items_equiped = extract<uint8_t>(serialization, j);
      // std::cout << "@@@Hero stats@@@" << std::endl
      //           << "max_hp: " << max_hp << " max_mana " << mana_max << "
      //           gold"
      //           << gold << " ghost mode " << ghost_mode << " items equiped "
      //           << items_equiped << "name size" << name_size << std::endl;
      // std::cout << "@@Deserializing items equiped@@" << std::endl;
      for (int x = items_equiped; x > 0; x--) {
        int current_item_slot = extract<uint8_t>(serialization, j);
        int current_item_id = extract<uint8_t>(serialization, j);
        // std::cout << "equiped " << current_item_id << " at "
        //           << current_item_slot << std::endl;
      }

      int items_inventory = extract<uint8_t>(serialization, j);
      // std::cout << "items in inventory: " << items_inventory << std::endl;
      // std::cout << "@@Deserializing items in invetory@@" << std::endl;
      for (int x = items_inventory; x > 0; x--) {
        int inventory_item_id = extract<uint8_t>(serialization, j);
        // std::cout << "item in inventory " << inventory_item_id << std::endl;
      }
    } else {
      npcs_or_others_detected++;
      // std::cout << "deserialized a ???? with id " << id << std::endl;
      // Deberia ser un NPC, no tiene mas atributos
    }
  }
  //std::cout << "Enviando: " << entities_quantity << " entidades" << std::endl;
  // std::cout << "monsters detecteD: " << monsters_detected << " heroes_detected " << heroes_detected << " npcs_or_others_detected " <<
  // npcs_or_others_detected << " drops detected " << drops_detected << std::endl;
}

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