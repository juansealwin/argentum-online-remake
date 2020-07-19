#include "deserializer.h"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

template <typename T>
// debe llamarse a este metodo si se necesita extraer del vector elementos de
// mas de 1 byte
T extract(const std::vector<unsigned char> &v, unsigned int &pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  pos += sizeof(T);
  return value;
}

Hero *deserialize_hero(std::vector<unsigned char> &serialization) {
  int entity_type, y, x, orientation, items_in_drop, drop_has_coins, name_size,
      class_id, affected_by, meditating, ghost_mode, close_to_npc,
      items_equiped, items_inventory;
  uint16_t id, max_hp, current_hp, level, mana_max, curr_mana, str,
      intelligence, agility, constitution, gold, xp_limit, current_xp;

  unsigned int j = 0;
  entity_type = extract<uint8_t>(serialization, j);

  max_hp = extract<uint16_t>(serialization, j);
  current_hp = extract<uint16_t>(serialization, j);
  level = extract<uint16_t>(serialization, j);
  affected_by = extract<uint8_t>(serialization, j);
  std::cout << "lvl: " << level << "maxhp: " << max_hp << "current_hp"
            << current_hp << std::endl;

  int name_size = extract<uint8_t>(serialization, j);
  std::string name;
  for (int x = 0; x < name_size; x++) {
    name += serialization.at(j);
    j++;
  }
  std::cout << "Name of the hero: " << name << std::endl;

  class_id = extract<uint8_t>(serialization, j);
  mana_max = (extract<uint16_t>(serialization, j));
  curr_mana = (extract<uint16_t>(serialization, j));
  str = (extract<uint16_t>(serialization, j));
  intelligence = (extract<uint16_t>(serialization, j));
  agility = (extract<uint16_t>(serialization, j));
  constitution = (extract<uint16_t>(serialization, j));
  gold = (extract<uint16_t>(serialization, j));
  xp_limit = (extract<uint16_t>(serialization, j));
  current_xp = (extract<uint16_t>(serialization, j));
  meditating = extract<uint8_t>(serialization, j);
  ghost_mode = extract<uint8_t>(serialization, j);
  close_to_npc = extract<uint8_t>(serialization, j);
  std::cout << "@@@Hero stats@@@" << std::endl
            << "max_hp: " << max_hp << " max_mana " << mana_max << "gold "
            << gold << " ghost mode " << ghost_mode << " items equiped "
            << items_equiped << "name size" << name_size << std::endl;

  // Agregamos los items equipados
  items_equiped = extract<uint8_t>(serialization, j);
  // std::cout << "@@Deserializing items equiped@@" << std::endl;
  for (int x = items_equiped; x > 0; x--) {
    int current_item_slot = extract<uint8_t>(serialization, j);
    int current_item_id = extract<uint8_t>(serialization, j);

    // completarrrrrrrrrrr
  }
  // std::cout << "items in inventory: " << items_inventory << std::endl;

  // Agregamos los items del inventario
  items_inventory = extract<uint8_t>(serialization, j);

  // std::cout << "@@Deserializing items in invetory@@" << std::endl;
  for (int x = items_inventory; x > 0; x--) {
    int current_item_id = extract<uint8_t>(serialization, j);

    // completarrrrrrrrrrr
  }

  // falta la parte del banco
  return nullptr;
}

/*
  int bank_size = extract<uint8_t>(status_serialized, j);
        // std::cout << "bank size is " << bank_size << std::endl;
        for (int x = 0; x < bank_size; x++) {
          int item = extract<uint8_t>(status_serialized, j);
          next_ui_status.add_item(BANK, get_item_texture(item));
          // std::cout << "item in bank: " << item << std::endl;;
        }

        // uint16_t gold = ntohs(extract<uint16_t>(status_serialized, j));
        // std::cout << "gold in bnak: " << gold << std::endl;
        next_ui_status.open_shop(BANK)
        */