#include <vector>
#include <sstream>
#include "client_handler.h"
#include <iostream>

ClientHandler::ClientHandler(Socket socket, ArgentumGame* game) : game(game) {
    this->peer_socket = std::move(socket);
}

ClientHandler::~ClientHandler() {
    this->join();
}

void ClientHandler::run() {
    std::cout << "connected to the game room :" 
    << game->get_room() << std::endl;
    while (alive) {
        unsigned char c = receive_request();
        std::cout<< c << std::endl;
        std::string message = "Ganaste";
        const unsigned char* response =
         reinterpret_cast<const unsigned char *>(message.c_str());
        uint16_t message_length = 7;
        send_response(response, &message_length);
        alive = false;
    }
    this->peer_socket.close();
}
unsigned char ClientHandler::receive_request() {
    return ServerProtocol::receive_command(this->peer_socket);
}

void ClientHandler::send_response
(const unsigned char* response, const uint16_t* size) {
    return ServerProtocol::send_response_to_command
           (this->peer_socket, response, size);
}

const bool ClientHandler::is_alive() {
    return this->alive;
}
