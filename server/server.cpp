#include "server.h"

Server::Server(const char *port, const char *map_cfg_file)
    : listener(port, map_cfg_file) {}

void Server::run() {
  this->listener.start();
  std::string input;
  while (input != "q") {
    std::cin >> input;
  }
  this->listener.stop_listening();
}
