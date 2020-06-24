#include "protected_map.h"

ProtectedMap::ProtectedMap() : read_map(nullptr), write_map(nullptr) {}

ProtectedMap::~ProtectedMap() {}

Game ProtectedMap::map_reader() {
  std::unique_lock<std::mutex> lock(block_maps);
  return *read_map;
}

void ProtectedMap::map_writer(std::map<int, CharacterStatus>& next_status) {
  std::unique_lock<std::mutex> lock(block_maps);

  std::map<int, CharacterStatus>::iterator it;
  std::map<int, CharacterStatus>::iterator it2;

  // Comprobamos si hay entidades que no están más en el mapa
  for (it = current_status.begin(); it != next_status.end(); it++) {
    it2 = next_status.find(it->first);
    // Si no están más, las borramos del current status y del mapa
    if (it2 == next_status.end()) {
      current_status.erase(it->first);
      write_map->clean_character(it->first);
    }
  }

  // Hacemos updates de las entidades que aun estan y creamos las nuevas
  for (it = next_status.begin(); it != next_status.end(); it++) {
    // Chequeamos si dicho personaje ya existia dentro del mapa
    it2 = current_status.find(it->first);

    if (it2 != current_status.end()) {
      // Chequeamos si dicho personaje se mantuvo cte. o se modifico
      if (!(it2->second.is_equal(it->second))) {
        // Si cambio hacemos un update del personaje
        write_map->update_character(it->first, it->second.get_x(),
                                      it->second.get_y());
      }
    } else {
      // Como no existe lo creamos
      write_map->load_character(it->second.get_type_character(), it->first,
                                  it->second.get_x(), it->second.get_y());
    }
    // Mofificamos/creamos el status para la proxima pasada
    current_status[it->first] = it->second;
  }
  // Copiamos todo el update en el mapa de lectura
  *read_map = *write_map;
}
