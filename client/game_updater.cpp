#include "game_updater.h"

GameUpdater::GameUpdater(ProtectedMap& map, Socket& socket)
    : protected_map(map), read_socket(socket) {}

GameUpdater::~GameUpdater() {}

void GameUpdater::run() {
  try {
    while (is_running) {
      // Recibimos las actualizaciones del mapa

      // Protocol::recieve_updates(read_socket, next_status);

      // Hacemos el write de los datos actualizados en el monitor de mapa
      protected_map.map_writer(next_status);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
