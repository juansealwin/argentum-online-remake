#include "protected_map.h"

ProtectedMap::ProtectedMap(int id_player, int screen_width, int screen_height) {
  read_map = new Game(id_player, screen_width, screen_height);
  write_map = new Game(id_player, screen_width, screen_height);
  current_status.clear();
}

ProtectedMap::~ProtectedMap() {
  delete read_map;
  delete write_map;
}

Game ProtectedMap::map_reader() {
  std::unique_lock<std::mutex> lock(block_maps);
  return *read_map;
}

void ProtectedMap::copy_buffer() {
  std::unique_lock<std::mutex> lock(block_maps);
  *read_map = *write_map;
}

void ProtectedMap::map_writer(std::map<int, CharacterStatus>& next_status) {
  std::map<int, CharacterStatus>::iterator it;
  std::map<int, CharacterStatus>::iterator it2;
  std::map<int, spellbound_t>::iterator it_afected;

  // Hacemos updates de las entidades que aun estan y creamos las nuevas
  for (it = next_status.begin(); it != next_status.end(); it++) {
    // Chequeamos si el personaje fue afectado por algo y si tiene alguna
    // animación en curso de otro hechizo
    if ((it->second.is_afected()) &&
        (characters_afected[it->first].lifetime == 0)) {
      characters_afected[it->first].type_spell = it->second.is_afected();
      characters_afected[it->first].lifetime = it->second.get_life_time();
    }

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
      write_map->load_character(it->first, it->second.get_type_character(),
                                it->second.get_x(), it->second.get_y());
    }

    // Si todavía queda resto de alguna animación de hechizo, lo actualizamos
    // y restamos al lifetime de lo que queda de dicha animación
    if (characters_afected[it->first].lifetime > 0) {
      write_map->update_spellbound(it->first,
                                   characters_afected[it->first].type_spell,
                                   characters_afected[it->first].lifetime);
      characters_afected[it->first].lifetime--;
    }

    // Mofificamos/creamos el status para la proxima pasada
    current_status[it->first] = it->second;
  }

  // Comprobamos si hay entidades que no están más en el mapa
  for (it = current_status.begin(); it != current_status.end(); it++) {
    it2 = next_status.find(it->first);
    // Si no están más, las borramos del current status, del mapa y de afectados
    if (it2 == next_status.end()) {
      current_status.erase(it->first);
      write_map->clean_character(it->first);

      characters_afected.erase(it->first);
    }
  }
}
