#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>

#include "client_listener.h"

class Server {
 public:
  explicit Server(const char *port, const char *map_cfg_file,
                  const char *entities_cfg_file);
  // Corre un servidor para que los clientes que se conecten
  // Juegen a GuessNumberGame
  void run();

 private:
  ClientListener listener;
};

#endif  // SERVER_H
