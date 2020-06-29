#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientCommandReceiver::ClientCommandReceiver(
    Socket& peer_socket, ArgentumGame* game,
    ThreadSafeQueue<Command*>* commands_queue)
    : game(game), peer_socket(peer_socket), commands_queue(commands_queue) {}

ClientCommandReceiver::~ClientCommandReceiver() { join(); }

void ClientCommandReceiver::stop() { this->alive = false; }

void ClientCommandReceiver::run() {
  while (alive) {
    CommandDTO* command_dto = Protocol::receive_command(peer_socket);
    if (command_dto != nullptr) {
      Command* command = CommandFactory::create_command(command_dto);
      std::cout << "Received a new command!" << std::endl;
      delete command_dto;
      commands_queue->push(command);
    }
    else {
      std::cerr << "Received unknown command or client stopped connection!" << std::endl;
      alive = false;
    }
  }
}

bool ClientCommandReceiver::is_alive() { return this->alive; }
