#include "players_saver_sender.h"

#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

PlayersSaverSender::PlayersSaverSender(
    BlockingThreadSafeQueue<
        std::tuple<std::string, std::vector<unsigned char>>*>*
        players_serializations_queue,
    FilesHandler& files_handler)
    : players_serializations_queue(players_serializations_queue),
      files_handler(files_handler),
      alive(true) {}

PlayersSaverSender::~PlayersSaverSender() {
  this->players_serializations_queue->close();
  this->alive = false;
  join();
  delete players_serializations_queue;
}

// ver de eliminar este metodo
void PlayersSaverSender::stop() {
  players_serializations_queue->close();
  // while (!players_serializations_queue->is_empty()) {
  //   Notification* n = notifications_queue->pop();
  //   delete n;
  // }
  this->alive = false;
}

void PlayersSaverSender::run() {
  while (alive) {
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
