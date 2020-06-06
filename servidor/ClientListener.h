#ifndef CLIENTLISTENER_H
#define CLIENTLISTENER_H

#include "../red/Socket.h"
#include "../utils/Thread.h"
#include "ClientHandler.h"
#include <list>
#include <vector>

class ClientListener : public Thread {
public:
    /*Crea un nuevo ClientListener que escuchara en el puerto port
    y utilizara numbers para asignarle a cada cliente que se conecte*/
    ClientListener(const char *port);

    ~ClientListener() override;
    /*Escucha nuevos clientes en el puerto 'port'.
    Por cada nuevo cliente que se conecte al puerto, crea a un nuevo
    ClientHandler al cual se le asigna un numero del vector numbers
    utilizando RoundRobin para que juege al juego GuessNumberGame */
    void run() override;
    //Deja de escuchar por nuevos clientes
    void stop_listening();

private:
    Socket server_socket;
    std::list<ClientHandler *> clients;
    /*Remueve a los clientes del vector clients
     que hayan muerto o hayan terminado de jugar
    */
    void garbage_collector();
};

#endif //CLIENTLISTENER_H
