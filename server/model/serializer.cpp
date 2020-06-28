#include "serializer.h"

#include "defensive_item.h"
#include "staff.h"
template <typename T>
// debe llamarse a este metodo si se necesita extraer del vector elementos de
// mas de 1 byte
T extract(const std::vector<unsigned char> &v, int &pos) {
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

std::vector<unsigned char> Serializer::serialize_game_status(
    ArgentumGame *game) {
  // serializacion actual:
  //<uint8_t>(notification id),<uint16_t>(id unico por entidad), <uint8_t>(id
  // del tipo de entidad), <uint8_t>(pos x), <uint8_t>(pos y), ....
  std::vector<unsigned char> serialization;
  uint8_t notification_id = 1;
  serialization.push_back(notification_id);
  for (auto &entity : game->entities) {
    uint16_t entity_id = htons(entity.first);
    unsigned int current_pos = serialization.size();
    serialization.resize(serialization.size() + sizeof(entity_id));
    std::memcpy(serialization.data() + current_pos, &entity_id,
                sizeof(entity_id));
    uint8_t entity_type = entity.second->type;
    uint8_t x = entity.second->x_position;
    uint8_t y = entity.second->y_position;
    serialization.push_back(entity_type);
    serialization.push_back(x);
    serialization.push_back(y);
  }

  //debug_deserialize(serialization);
  return serialization;
}

std::vector<unsigned char> Serializer::serialize_game_status_v2(
    ArgentumGame *game) {
  std::vector<unsigned char> serialization;
  uint8_t notification_id = 1;
  serialization.push_back(notification_id);
  for (auto &entity : game->entities) {
    uint16_t entity_id = htons(entity.first);
    insert(serialization, entity_id);
    uint8_t entity_type = entity.second->type;
    uint8_t x = entity.second->x_position;
    uint8_t y = entity.second->y_position;
    uint8_t orientation = entity.second->orientation;
    serialization.push_back(entity_type);
    serialization.push_back(x);
    serialization.push_back(y);
    serialization.push_back(orientation);
    if (dynamic_cast<Monster *>(entity.second) != nullptr) {
      serialize_monster(serialization, dynamic_cast<Monster *>(entity.second));
    } else if (dynamic_cast<Hero *>(entity.second) != nullptr) {
      serialize_hero(serialization, dynamic_cast<Hero *>(entity.second));
    } else {
      // es un NPC o algun error hubo.
    }
  }

  debug_deserialize(serialization);
  return serialization;
}

void Serializer::serialize_monster(std::vector<unsigned char> &serialization,
                                   Monster *m) {
  uint16_t max_hp = htons(m->max_hp);
  uint16_t current_hp = htons(m->current_hp);
  uint16_t level = htons(m->level);
  insert(serialization, max_hp);
  insert(serialization, current_hp);
  insert(serialization, level);
}

void Serializer::serialize_hero(std::vector<unsigned char> &serialization,
                                Hero *h) {
  /************** serializacion del estado del heroe ***************/
  uint16_t max_hp = htons(h->max_hp);
  uint16_t current_hp = htons(h->current_hp);
  uint16_t level = htons(h->level);
  // aca meter el nombre
  uint8_t name_size = h->name.size();
  uint8_t class_id = h->class_id;
  uint16_t mana_max = htons(h->max_mana);
  uint16_t curr_mana = htons(h->current_mana);
  uint16_t str = htons(h->strength);
  uint16_t intelligence = htons(h->intelligence);
  uint16_t agility = htons(h->agility);
  uint16_t constitution = htons(h->constitution);
  uint16_t gold = htons(h->gold);
  uint16_t xp_limit = htons(h->next_level_xp_limit);
  uint16_t current_xp = htons(h->experience);
  uint8_t meditating = (int)h->meditating;
  uint8_t ghost_mode = (int)h->ghost_mode;

  insert(serialization, max_hp);
  insert(serialization, current_hp);
  insert(serialization, level);
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

void Serializer::debug_deserialize(std::vector<unsigned char> serialization) {
  std::cout << "vector size is " << serialization.size() << std::endl;
  int j = 1;
  while (j < serialization.size()) {
    uint16_t id = ntohs(extract<uint16_t>(serialization, j));
    int entity_type = extract<uint8_t>(serialization, j);
    int x = extract<uint8_t>(serialization, j);
    int y = extract<uint8_t>(serialization, j);
    int orientation = extract<uint8_t>(serialization, j);
    // std::cout << "Entity id: " << id << ", type: " << entity_type
    //           << ", x_pos: " << x << ", y_pos: " << y
    //           << "orientation: " << orientation << std::endl;
    if (is_monster(entity_type)) {
      uint16_t max_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t current_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t level = ntohs(extract<uint16_t>(serialization, j));
      // std::cout << "Monster: lvl: " << level << "maxhp: " << max_hp
      //           << "current_hp" << current_hp << std::endl;
    } else if (is_hero(entity_type)) {
      uint16_t max_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t current_hp = ntohs(extract<uint16_t>(serialization, j));
      uint16_t level = ntohs(extract<uint16_t>(serialization, j));
      int name_size = extract<uint8_t>(serialization, j);
      std::string name;
      for (int x = 0; x < name_size; x++) {
        name += serialization.at(j);
        j++;
      }
      // std::cout << "Name of the hero: " << name << std::endl;
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
      int ghost_mode = extract<uint8_t>(serialization, j);
      int items_equiped = extract<uint8_t>(serialization, j);
      // std::cout << "@@@Hero stats@@@" << std::endl
      //           << "max_hp: " << max_hp << " max_mana " << mana_max << " gold
      //           "
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
      // Deberia ser un NPC, no tiene mas atributos
    }
  }
}

/************* METODOS PRIVADOS **************/

bool Serializer::vector_contains(std::vector<uint8_t> v, uint8_t x) {
  if (std::find(v.begin(), v.end(), x) != v.end()) return true;
  return false;
}

// bool Serializer::is_npc(uint8_t t) {
//   const std::vector<uint8_t> npcs = {33, 34, 35};
//   return vector_contains(npcs, t);
// }

bool Serializer::is_hero(uint8_t t) {
  const std::vector<uint8_t> heroes = {25, 26, 27, 28};
  return vector_contains(heroes, t);
}

bool Serializer::is_monster(uint8_t t) {
  const std::vector<uint8_t> monsters = {29, 30, 31, 32};
  return vector_contains(monsters, t);
}