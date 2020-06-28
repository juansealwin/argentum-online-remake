#include "game_updater.h"

template <typename T>
T extract(const std::vector<unsigned char>& v, int pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  return value;
}

GameUpdater::GameUpdater(ProtectedMap& map, Socket& socket)
    : protected_map(map), read_socket(socket) {}

GameUpdater::~GameUpdater() {}

void GameUpdater::run() {
  try {
    while (is_running) {
      std::cout<<"GameUpdater: por recibir una notificacion"<<std::endl;
      // Recibimos las actualizaciones del mapa
      Protocol::receive_notification(read_socket, status_serialized);
std::cout<<"GameUpdater: por deserializar la info"<<std::endl;
      // Deserializamos la información recibida por el protocolo
      deserialize_status();
std::cout<<"GameUpdater: escribiendo en el protected map"<<std::endl;
      // Hacemos el write de los datos actualizados en el monitor de mapa
      protected_map.map_writer(next_status);
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
    int x = (int)status_serialized.at(j);
    j++;
    int y = (int)status_serialized.at(j);
    next_status[id] = CharacterStatus(entity_type, x, y);
    j++;
  }
}
