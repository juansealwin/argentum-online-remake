#include "client_handler.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientHandler::ClientHandler(Socket socket, ArgentumGame* game) : game(game) {
  this->peer_socket = std::move(socket);
}

ClientHandler::~ClientHandler() { this->join(); }

void ClientHandler::run() {
  std::cout << "connected to the game room :" << game->get_room() << std::endl;
  while (alive) {
    Json::Value command = Protocol::receiveMessage(this->peer_socket);
    std::string message = "Ganaste";
    const unsigned char* response =
        reinterpret_cast<const unsigned char*>(message.c_str());
    uint16_t message_length = 7;
    // send_response(response, &message_length);
    // Protocol::sendMessage(this->peer_socket);
    alive = false;
  }
  this->peer_socket.close();
}

bool ClientHandler::is_alive() { return this->alive; }
