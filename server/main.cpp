#include <fstream>
#include <iostream>
#include <vector>

#include "server.h"

#define ARGC 3
#define SUCCESS 0
#define ERROR 1

int main(int argc, char *argv[]) {
  if (argc != ARGC) {
    std::cerr << "Error: argumentos invalidos. Correr con ./server <map.cfg> <entities.cfg>" << std::endl;
    return ERROR;
  }
  char *port = argv[1];
  // Recibir archivo de configuracion y pasarlo por parametro al server
  Server server(port, argv[2]);
  server.run();
  return SUCCESS;
}
