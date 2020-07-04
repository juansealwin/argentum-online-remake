#include "game_updater.h"

template <typename T>
T extract(const std::vector<unsigned char> &v, unsigned int &pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  pos += sizeof(T);
  return value;
}

GameUpdater::GameUpdater(ProtectedMap& map, Socket& socket, bool& run)
    : protected_map(map), read_socket(socket), is_running(run) {}

GameUpdater::~GameUpdater() {}

void GameUpdater::run() {
  try {
    while (is_running) {
      // Recibimos las actualizaciones del mapa
      Protocol::receive_notification(read_socket, status_serialized);

      // Deserializamos la información recibida
      deserialize_status();

      // Escribimos la información en el mapa protegido
      protected_map.map_writer(next_status);

      // Copiamos todo el update en el mapa de lectura
      protected_map.copy_buffer();

      // Limpiamos el mapa para la proxima pasada
      next_status.clear();
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

// void GameUpdater::deserialize_status() {
//   int j = 1;
//   while (j < status_serialized.size()) {
//     uint16_t id = ntohs(extract<uint16_t>(status_serialized, j));
//     j += 2;
//     int entity_type = (int)status_serialized.at(j);
//     j++;
//     int y = (int)status_serialized.at(j);
//     j++;
//     int x = (int)status_serialized.at(j);
//     /*
//       std::cout << "Entity id: " << (int)id << ", type: " << entity_type
//                 << ", x_pos: " << x << ", y_pos: " << y << std::endl;*/
//     int k = 0;
        
//     next_status[(int)id] = CharacterStatus(entity_type, x, y, k);
//     j++;
//   }
// }


bool vector_contains(std::vector<uint8_t> v, uint8_t x) {
  if (std::find(v.begin(), v.end(), x) != v.end()) return true;
  return false;
}

bool is_hero(uint8_t t) {
  const std::vector<uint8_t> heroes = {25, 26, 27, 28};
  return vector_contains(heroes, t);
}

bool is_monster(uint8_t t) {
  const std::vector<uint8_t> monsters = {29, 30, 31, 32};
  return vector_contains(monsters, t);
}

void GameUpdater::deserialize_status() {
  //std::cout << "vector size is " << status_serialized.size() << std::endl;
  unsigned int j = 1;
  while (j < status_serialized.size()) {
    uint16_t id = ntohs(extract<uint16_t>(status_serialized, j));
    int entity_type = extract<uint8_t>(status_serialized, j);
    int y = extract<uint8_t>(status_serialized, j);
    int x = extract<uint8_t>(status_serialized, j);
    int k = 0;
    next_status[(int)id] = CharacterStatus(entity_type, x, y, k);
    int orientation = extract<uint8_t>(status_serialized, j);
    // std::cout << "Entity id: " << id << ", type: " << entity_type
    //           << ", x_pos: " << x << ", y_pos: " << y
    //           << "orientation: " << orientation << std::endl;
    if (is_monster(entity_type)) {
      uint16_t max_hp = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t current_hp = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t level = ntohs(extract<uint16_t>(status_serialized, j));
      uint8_t affected_by = extract<uint8_t>(status_serialized, j);
      // std::cout << "Monster: lvl: " << level << "maxhp: " << max_hp
      //           << "current_hp" << current_hp << std::endl;
    } else if (is_hero(entity_type)) {
      uint16_t max_hp = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t current_hp = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t level = ntohs(extract<uint16_t>(status_serialized, j));
      uint8_t affected_by = extract<uint8_t>(status_serialized, j);
      int name_size = extract<uint8_t>(status_serialized, j);
      std::string name;
      for (int x = 0; x < name_size; x++) {
        name += status_serialized.at(j);
        j++;
      }
      // std::cout << "Name of the hero: " << name << std::endl;
      int class_id = extract<uint8_t>(status_serialized, j);
      uint16_t mana_max = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t curr_mana = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t str = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t intelligence = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t agility = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t constitution = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t gold = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t xp_limit = ntohs(extract<uint16_t>(status_serialized, j));
      uint16_t current_xp = ntohs(extract<uint16_t>(status_serialized, j));
      int meditating = extract<uint8_t>(status_serialized, j);
      int ghost_mode = extract<uint8_t>(status_serialized, j);
      int items_equiped = extract<uint8_t>(status_serialized, j);
      // std::cout << "@@@Hero stats@@@" << std::endl
      //           << "max_hp: " << max_hp << " max_mana " << mana_max << "
      //           gold"
      //           << gold << " ghost mode " << ghost_mode << " items equiped "
      //           << items_equiped << "name size" << name_size << std::endl;
      // std::cout << "@@Deserializing items equiped@@" << std::endl;
      for (int x = items_equiped; x > 0; x--) {
        int current_item_slot = extract<uint8_t>(status_serialized, j);
        int current_item_id = extract<uint8_t>(status_serialized, j);
        // std::cout << "equiped " << current_item_id << " at "
        //           << current_item_slot << std::endl;
      }

      int items_inventory = extract<uint8_t>(status_serialized, j);
      // std::cout << "items in inventory: " << items_inventory << std::endl;
      // std::cout << "@@Deserializing items in invetory@@" << std::endl;
      for (int x = items_inventory; x > 0; x--) {
        int inventory_item_id = extract<uint8_t>(status_serialized, j);
        // std::cout << "item in inventory " << inventory_item_id << std::endl;
      }
    } else {
      // Deberia ser un NPC, no tiene mas atributos
    }
  }
}
