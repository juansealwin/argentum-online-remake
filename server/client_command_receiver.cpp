#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientCommandReceiver::ClientCommandReceiver(Socket& peer_socket,
                                             ArgentumGame* game)
    : game(game), peer_socket(peer_socket) {}

ClientCommandReceiver::~ClientCommandReceiver() {
  // std::cout << "Trying to join receiver" << std::endl;
  join();
}

void ClientCommandReceiver::stop() { this->alive = false; }

void ClientCommandReceiver::run() {
  std::cout << "receiver, game room :" << game->get_room() << std::endl;
  int loops = 0;
  while (alive) {
    std::cout << "In receiver thread" << std::endl;
    /*descomentar luego de tests
    Json::Value command = Protocol::receiveMessage(this->peer_socket);*/
    unsigned char c = Protocol::receive_command(this->peer_socket);
    std::cout << "@@@@@@received@@@@@@@: " << c << std::endl;
    loops++;
    if (loops == 5) {
      std::cout << "alive was set to false" << std::endl;
      std::cout << "finishing receiv sender run()";
      alive = false;
    }
  }
}

bool ClientCommandReceiver::is_alive() { return this->alive; }
