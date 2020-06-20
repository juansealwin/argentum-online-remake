#include "client_handler.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientHandler::ClientHandler(Socket socket, ArgentumGame* game) : game(game) {
  this->peer_socket = std::move(socket);
  sender = new ClientNotificationSender(peer_socket, game);
  receiver = new ClientCommandReceiver(peer_socket, game);
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
   return (this->receiver->is_alive() || this->sender->is_alive());
}
