#include "game_updater.h"

template <typename T>
T extract(const std::vector<unsigned char>& v, unsigned int& pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  pos += sizeof(T);
  return value;
}

GameUpdater::GameUpdater(int id, ProtectedMap& map, Socket& socket, bool& run)
    : protected_map(map), read_socket(socket), is_running(run), id_hero(id) {}

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
      protected_map.copy_buffer(next_ui_status);

      // Limpiamos el mapa para la proxima pasada
      next_status.clear();
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

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
  unsigned int j = 1;

  // Declaramos las variables necesarias para extraer la informacion int para
  // las de 1 byte y uint16_t para las de 2 bytes
  int entity_type, y, x, k, orientation, affected_by, name_size, class_id,
      meditating, ghost_mode, items_equiped, current_item_slot, current_item_id,
      items_inventory;
  uint16_t id, max_hp, current_hp, level, mana_max, curr_mana, str,
      intelligence, agility, constitution, gold, xp_limit, current_xp;

  while (j < status_serialized.size()) {
    id = ntohs(extract<uint16_t>(status_serialized, j));
    entity_type = extract<uint8_t>(status_serialized, j);
    y = extract<uint8_t>(status_serialized, j);
    x = extract<uint8_t>(status_serialized, j);
    k = 0;
    next_status[(int)id] = CharacterStatus(entity_type, x, y, k);
    orientation = extract<uint8_t>(status_serialized, j);
    // std::cout << "Entity id: " << id << ", type: " << entity_type
    //           << ", x_pos: " << x << ", y_pos: " << y
    //           << "orientation: " << orientation << std::endl;
    // Dejamos afuera a los npc de compra y venta
    if (is_hero(entity_type) || is_monster(entity_type)) {
      max_hp = ntohs(extract<uint16_t>(status_serialized, j));
      current_hp = ntohs(extract<uint16_t>(status_serialized, j));
      level = ntohs(extract<uint16_t>(status_serialized, j));
      affected_by = extract<uint8_t>(status_serialized, j);
      // std::cout << "Monster: lvl: " << level << "maxhp: " << max_hp
      //           << "current_hp" << current_hp << std::endl;
    }
    if (is_hero(entity_type)) {
      int name_size = extract<uint8_t>(status_serialized, j);
      std::string name;
      for (int x = 0; x < name_size; x++) {
        name += status_serialized.at(j);
        j++;
      }
      // std::cout << "Name of the hero: " << name << std::endl;
      class_id = extract<uint8_t>(status_serialized, j);
      mana_max = ntohs(extract<uint16_t>(status_serialized, j));
      curr_mana = ntohs(extract<uint16_t>(status_serialized, j));
      str = ntohs(extract<uint16_t>(status_serialized, j));
      intelligence = ntohs(extract<uint16_t>(status_serialized, j));
      agility = ntohs(extract<uint16_t>(status_serialized, j));
      constitution = ntohs(extract<uint16_t>(status_serialized, j));
      gold = ntohs(extract<uint16_t>(status_serialized, j));
      xp_limit = ntohs(extract<uint16_t>(status_serialized, j));
      current_xp = ntohs(extract<uint16_t>(status_serialized, j));
      meditating = extract<uint8_t>(status_serialized, j);
      ghost_mode = extract<uint8_t>(status_serialized, j);

      // Si son los datos del cliente lo cargamos en la UI
      // Cargamos a los datos visibles de la próxima interfaz
      if (id == id_hero)
        next_ui_status = UIStatus(name, level, max_hp, current_hp, mana_max,
                                  curr_mana, xp_limit, current_xp, gold);
      items_equiped = extract<uint8_t>(status_serialized, j);
      // std::cout << "@@@Hero stats@@@" << std::endl
      //           << "max_hp: " << max_hp << " max_mana " << mana_max << "
      //           gold"
      //           << gold << " ghost mode " << ghost_mode << " items equiped "
      //           << items_equiped << "name size" << name_size << std::endl;
      // std::cout << "@@Deserializing items equiped@@" << std::endl;
      for (int x = items_equiped; x > 0; x--) {
        current_item_slot = extract<uint8_t>(status_serialized, j);
        current_item_id = extract<uint8_t>(status_serialized, j);

        // Si son los items del cliente, queremos mostrarlos en la UI
        if (id == id_hero)
          next_ui_status.add_item(current_item_id, current_item_slot);
        // std::cout << "equiped " << current_item_id << " at "
        //           << current_item_slot << std::endl;
      }

      items_inventory = extract<uint8_t>(status_serialized, j);
      // std::cout << "items in inventory: " << items_inventory << std::endl;
      // std::cout << "@@Deserializing items in invetory@@" << std::endl;
      for (int x = items_inventory; x > 0; x--) {
        current_item_id = extract<uint8_t>(status_serialized, j);

        // Si son los items del cliente, queremos mostrarlos en la UI
        if (id == id_hero) next_ui_status.add_item(current_item_id);
        // std::cout << "item in inventory " << inventory_item_id << std::endl;
      }
    } else {
      // Deberia ser un NPC, no tiene mas atributos
    }
  }
}
