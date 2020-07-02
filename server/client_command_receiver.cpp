#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientCommandReceiver::ClientCommandReceiver(
    Socket& peer_socket, ArgentumGame* game,
    ThreadSafeQueue<Command*>* commands_queue, unsigned int hero_id)
    : game(game),
      peer_socket(peer_socket),
      commands_queue(commands_queue),
      hero_id(hero_id),
      alive(true) {}

ClientCommandReceiver::~ClientCommandReceiver() { join(); }

void ClientCommandReceiver::stop() { this->alive = false; }

void ClientCommandReceiver::run() {
  std::cout <<  "Starting command receiver, hero id: " << hero_id << std::endl;
  while (alive) {
    CommandDTO* command_dto = Protocol::receive_command(peer_socket);
    if (command_dto != nullptr) {
      Command* command = CommandFactory::create_command(command_dto, hero_id);
      delete command_dto;
      commands_queue->push(command);
    } else {
      std::cerr << "Received unknown command or client stopped connection!"
                << std::endl;
      alive = false;
    }
  }
}

bool ClientCommandReceiver::is_alive() { return this->alive; }
