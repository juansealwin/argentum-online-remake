#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientCommandReceiver::ClientCommandReceiver(
    Socket &peer_socket, unsigned int game_room,
    ThreadSafeQueue<Command *> *commands_queue, unsigned int hero_id,
    std::vector<ArgentumGame *> &game_rooms)
    : peer_socket(peer_socket),
      current_game_room(game_room),
      commands_queue(commands_queue),
      hero_id(hero_id),
      alive(true),
      game_rooms(game_rooms) {}

ClientCommandReceiver::~ClientCommandReceiver() { join(); }

void ClientCommandReceiver::stop() { this->alive = false; }

void ClientCommandReceiver::run() {
  std::cout << "Starting command receiver, hero id: " << hero_id << "at room "
            << current_game_room << " total rooms are " << game_rooms.size()
            << std::endl;
  while (alive) {
    CommandDTO *command_dto = Protocol::receive_command(peer_socket);
    if (command_dto != nullptr) {
      if (command_blocker.can_process(command_dto)) {
        Command *command = CommandFactory::create_command(command_dto, hero_id);
        commands_queue->push(command);
      }
      delete command_dto;
    } else {
      std::cerr << "Received unknown command or client stopped connection!"
                << std::endl;
      alive = false;
    }
  }
  std::cout << "stopping command receiver" << std::endl;
}

bool ClientCommandReceiver::is_alive() { return this->alive; }
