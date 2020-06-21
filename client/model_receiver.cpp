#include "model_receiver.h"

ModelReceiver::ModelReceiver(BlockingMap& b_map) : blocking_map(b_map) {
  is_running = true;
}

ModelReceiver::~ModelReceiver() {}

void ModelReceiver::run() {
  try {
    while (is_running) {
      /* usando el protocolo deberia cargarse todo el map_updated */

      // courier.receiveMap(map_updated);

      /* luego de haberse cargado habria que cargar todo el mapa en el mapa
       * bloqueante para que el updater lo pueda leer mas tarde */

      // blocking_map.updateMap(map_updated);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}