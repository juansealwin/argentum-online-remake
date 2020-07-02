#include "game_updater.h"

template <typename T>
T extract(const std::vector<unsigned char>& v, int pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
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
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void GameUpdater::deserialize_status() {
  int j = 1;
  while (j < status_serialized.size()) {
    uint16_t id = ntohs(extract<uint16_t>(status_serialized, j));
    j += 2;
    int entity_type = (int)status_serialized.at(j);
    j++;
    int y = (int)status_serialized.at(j);
    j++;
    int x = (int)status_serialized.at(j);
    /*if (id == 15)
      std::cout << "Entity id: " << (int)id << ", type: " << entity_type
                << ", x_pos: " << x << ", y_pos: " << y << std::endl;*/
    next_status[(int)id] = CharacterStatus(entity_type, x, y, 1);
    j++;
  }
}
