#include <iostream>
#include "server_Server.h"

Server::Server(const char *port) :
    listener(port) {}

void Server::run() {
    this->listener.start();
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }
    this->listener.stop_listening();
}
