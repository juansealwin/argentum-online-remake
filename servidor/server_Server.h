#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include "ClientListener.h"

class Server {
public:
    explicit Server(const char *port);
    //Corre un servidor para que los clientes que se conecten 
    //Juegen a GuessNumberGame
    void run();

private:
    ClientListener listener;
};


#endif //SERVER_H
