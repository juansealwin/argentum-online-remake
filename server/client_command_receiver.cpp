#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientCommandReceiver::ClientCommandReceiver(
    Socket& peer_socket, ArgentumGame* game,
    ThreadSafeQueue<Command*>* commands_queue)
    : game(game), peer_socket(peer_socket),
    commands_queue(commands_queue) {}

ClientCommandReceiver::~ClientCommandReceiver() {
  // std::cout << "Trying to join receiver" << std::endl;
  join();
}

void ClientCommandReceiver::stop() { this->alive = false; }

void ClientCommandReceiver::run() {
  //std::cout << "receiver, game room :" << game->get_room() << std::endl;
  int loops = 0;
  while (alive) {


/*  Despues de que el protocol este listo:   
    Command *c = Protocol::receive_command(this->peer_socket);
    commands_queue->push(c); 
    
    o

    vector<unsigned char c> c = protocol::receive_command(socket)
    Command *c = factory(c)
    commands_queue->push(c); 

*/










    
    /*descomentar luego de tests
    Json::Value command = Protocol::receiveMessage(this->peer_socket);*/
    unsigned char c = Protocol::receive_command(this->peer_socket);
    loops++;
    if (loops == 5) {
      alive = false;
    }
  }
}

bool ClientCommandReceiver::is_alive() { return this->alive; }
