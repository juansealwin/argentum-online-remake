#include "client_handler.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientHandler::ClientHandler(
    Socket socket, unsigned int game_room,
    ThreadSafeQueue<Command *> *commands_queue,
    BlockingThreadSafeQueue<Notification *> *notifications_queue,
    unsigned int hero_id, std::vector<ArgentumGame *> &games)
    :  notifications_queue(notifications_queue) {
  this->peer_socket = std::move(socket);
  sender = new ClientNotificationSender(peer_socket, notifications_queue);
  receiver =
      new ClientCommandReceiver(peer_socket, game_room, commands_queue, hero_id, std::ref(games));
  sender->start();
  receiver->start();
}

ClientHandler::~ClientHandler() {
  this->sender->stop();
  this->receiver->stop();
  delete sender;
  delete receiver;
  this->peer_socket.close();
}

bool ClientHandler::is_alive() {
  return this->receiver->is_alive() || this->sender->is_alive();
}
