#include "server_Server.h"
#include <fstream>
#include <iostream>
#include <vector>

#define NUMBERS_LENGTH 3
#define ARGC 3
#define SUCCESS 0
#define ERROR 1

int main(int argc, char *argv[]) {
    if (argc != ARGC) { 
    	std::cerr << "Error: argumentos invalidos." << std::endl;
    	return ERROR;
    }
    char *port = argv[1];
    //Recibir archivo de configuracion y pasarlo por parametro al server
    Server server(port);
    server.run();
    return SUCCESS;
}
