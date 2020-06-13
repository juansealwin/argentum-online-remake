#ifndef CLIENT_LISTENER_H
#define CLIENT_LISTENER_H

#include <list>
#include <vector>

#include "argentum_game.h"
#include "client_handler.h"
#include "common_socket.h"
#include "thread.h"

class ClientListener : public Thread {
 public:
  /*Crea un nuevo ClientListener que escuchara en el puerto port
  y utilizara numbers para asignarle a cada cliente que se conecte*/
  explicit ClientListener(const char *port);

  ~ClientListener() override;
  /*Escucha nuevos clientes en el puerto 'port'.
  Por cada nuevo cliente que se conecte al puerto, crea a un nuevo
  ClientHandler al cual se le asigna un numero del vector numbers
  utilizando RoundRobin para que juege al juego GuessNumberGame */
  void run() override;
  // Deja de escuchar por nuevos clientes
  void stop_listening();

 private:
  std::vector<ArgentumGame *> games;
  Socket server_socket;
  std::list<ClientHandler *> clients;
  /*Remueve a los clientes del vector clients
   que hayan muerto o hayan terminado de jugar
  */
  void garbage_collector();
};

#endif  // CLIENTLISTENER_H
