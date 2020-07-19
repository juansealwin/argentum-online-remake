#include "server.h"

Server::Server(const char *port, const char *entities_cfg_file)
    : listener(port, entities_cfg_file) {}

void Server::run() {
  srand((unsigned) time(0));
  this->listener.start();
  std::string input;
  while (input != "q") {
    std::cin >> input;
  }
  this->listener.stop_listening();
}
