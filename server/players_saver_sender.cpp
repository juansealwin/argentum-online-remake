#include "players_saver_sender.h"

#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

PlayersSaverSender::PlayersSaverSender(
    BlockingThreadSafeQueue<
        std::tuple<std::string, std::vector<unsigned char>>*>*
        players_serializations_queue,
    FilesHandler& files_handler, bool periodic_mode,
    std::vector<ArgentumGame*>& rooms)
    : players_serializations_queue(players_serializations_queue),
      files_handler(files_handler),
      periodic_mode(periodic_mode),
      alive(true),
      rooms(rooms) {
  // if (periodic_mode == true) {
  //   last_update_time = std::chrono::high_resolution_clock::now();
  // }
}

PlayersSaverSender::~PlayersSaverSender() {
  this->players_serializations_queue->close();
  this->alive = false;
  join();
  delete players_serializations_queue;
}

void PlayersSaverSender::run() {
  while (alive) {
    if (periodic_mode) {
      // auto actual_time = std::chrono::high_resolution_clock::now();
      // auto time_difference = actual_time - last_update_time;
      // std::cout << time_difference.count() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(10000));
      // if (time_difference.count() >= 1000000000) {  // usar archivo config
      std::cout << "Se actualizan a todos los jugadores en archivo\n";
      std::vector<std::map<unsigned int, Hero*>> heroes_copy;
      // Para evitar errores por si justo un jugador cambia de mapa
      for (int i = 0; i < rooms.size(); i++) {
        heroes_copy.emplace_back(rooms[i]->heroes);
      }

      for (int i = 0; i < heroes_copy.size(); i++) {
        for (auto const& hero_tuple : heroes_copy[i]) {
          // El jugador pudo haberse desconectado
          Hero* hero = hero_tuple.second;
          if (hero != nullptr) {
            const std::string hero_name = hero->get_name();
            std::vector<unsigned char> serialization =
                files_handler.get_serialization_of_hero(hero);
            files_handler.save_player_status(serialization, hero_name);
          }
        }
      }
      //}
      // last_update_time = actual_time;
    } else {
      if (players_serializations_queue->is_closed()) break;
      std::tuple<std::string, std::vector<unsigned char>>* tuple =
          players_serializations_queue->pop();
      if (tuple) {
        files_handler.save_player_status(std::get<1>(*tuple),
                                         std::get<0>(*tuple));
        delete tuple;
      }
    }
  }
}
