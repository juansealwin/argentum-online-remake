#include "protected_map.h"

ProtectedMap::ProtectedMap(int id_player, int screen_width, int screen_height,
                           int initial_map) {
  /*read_map =
      new Game(id_player, screen_width, screen_height, map_t(initial_map));
  write_map =
      new Game(id_player, screen_width, screen_height, map_t(initial_map));*/
  read_map = std::unique_ptr<Game>(
      new Game(id_player, screen_width, screen_height, map_t(initial_map)));
  write_map = std::unique_ptr<Game>(
      new Game(id_player, screen_width, screen_height, map_t(initial_map)));
  current_status.clear();
  characters_afected.clear();
}

ProtectedMap::~ProtectedMap() {}

void ProtectedMap::map_reader(Game& game, UIStatus& renderer_ui, std::vector<sound_t>& current_sounds) {
  std::unique_lock<std::mutex> lock(block_maps);
  renderer_ui = current_ui_status;
  game = *read_map;
  current_sounds = incomin_sounds;
  incomin_sounds.clear();
}

void ProtectedMap::copy_buffer(UIStatus& next_ui_status) {
  std::unique_lock<std::mutex> lock(block_maps);
  current_ui_status = next_ui_status;
  *read_map = *write_map;
}

void ProtectedMap::map_writer(std::map<int, EntityStatus>& next_status,
                              map_t& new_map) {
  std::map<int, EntityStatus>::iterator it;
  std::map<int, EntityStatus>::iterator it2;
  std::map<int, spellbound_t>::iterator it_afected;

  // Verificamos si hubo cambio de mapa
  if (new_map != CURRENT_MAP) {
    // Limpiamos el mapa de personajes
    write_map->clean_all_characters(false);

    // Limpiamos los mapas de estados del mapa viejo
    characters_afected.clear();

    // Cambiamos el nuevo mapa
    write_map->change_map(new_map);

    // Ahora el nuevo mapa es el mapa actual
    new_map = CURRENT_MAP;
  }

  // Hacemos updates de las entidades que aun estan y creamos las nuevas
  for (it = next_status.begin(); it != next_status.end(); it++) {
    // Chequeamos si el personaje fue afectado por algo y si tiene alguna
    // animación en curso de otro hechizo
    if (it->second.is_afected() != ID_NULL) {
      if (characters_afected[it->first].lifetime == 0) {
        characters_afected[it->first].type_spell = it->second.is_afected();
        characters_afected[it->first].lifetime = it->second.get_life_time();
      }
    }
    // Chequeamos si dicha entidad ya existia dentro del mapa
    it2 = current_status.find(it->first);

    if (it2 != current_status.end() && (it->second.get_type_entity() != ITEM)) {
      // Chequeamos si dicho personaje se mantuvo cte. o se modifico
      if (!(it2->second.is_equal(it->second))) {
        // Si cambio hacemos un update del personaje
        write_map->update_character(
            it->first, it->second.get_type_entity(), it->second.get_x(),
            it->second.get_y(), it->second.get_orientation(),
            it->second.is_ghost(), it->second.is_meditating(),
            it->second.get_equipped(HELMET), it->second.get_equipped(ARMOR),
            it->second.get_equipped(SHIELD), it->second.get_equipped(WEAPON), incomin_sounds);
      }
    } else {
      // Como no existe la creamos
      // Vemos si es un personaje o un item estático
      if (it->second.get_type_entity() == ITEM)
        write_map->load_item(it->first, it->second.get_item(),
                             it->second.get_x(), it->second.get_y());
      else
        write_map->load_character(
            it->first, it->second.get_type_entity(), it->second.get_x(),
            it->second.get_y(), it->second.get_orientation(),
            it->second.is_ghost(), it->second.get_equipped(HELMET),
            it->second.get_equipped(ARMOR), it->second.get_equipped(SHIELD),
            it->second.get_equipped(WEAPON));
    }

    // Mofificamos/creamos el status para la proxima pasada
    current_status[it->first] = it->second;
  }

  // Si todavía queda resto de alguna animación de hechizo, lo actualizamos
  // y restamos al lifetime de lo que queda de dicha animación
  for (it_afected = characters_afected.begin();
       it_afected != characters_afected.end(); it_afected++) {
    if (it_afected->second.lifetime >= 0) {
      write_map->update_spellbound(it_afected->first,
                                   it_afected->second.type_spell,
                                   it_afected->second.lifetime);
      it_afected->second.lifetime--;
      // Si se termino el lifetime del hechizo borramos la id del pj afectado
    } else if (it_afected->second.lifetime == -1) {
      characters_afected.erase(it_afected->first);
    }
  }

  // Comprobamos si hay entidades que no están más en el mapa
  for (it = current_status.begin(); it != current_status.end();) {
    it2 = next_status.find(it->first);
    it_afected = characters_afected.find(it->first);
    // Si no están y además no tienen una animación en curso encima, las
    // borramos del current status y del mapa
    if (it2 == next_status.end() && it_afected == characters_afected.end()) {
      write_map->clean_entity(it->first, it->second.get_type_entity());
      it = current_status.erase(it);
    } else {
      it++;
    }
  }
}
