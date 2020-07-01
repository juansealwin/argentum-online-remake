#ifndef CLIENT_LISTENER_H
#define CLIENT_LISTENER_H

#include <list>
#include <vector>

#include "../util/thread_safe_queue.h"
#include "argentum_game.h"
#include "client_handler.h"
#include "common_socket.h"
#include "thread.h"
#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "protocol.h"
#include "starting_info_notification.h"
class ClientListener : public Thread {
 public:
  /*Crea un nuevo ClientListener que escuchara en el puerto port
  y utilizara numbers para asignarle a cada cliente que se conecte*/
  explicit ClientListener(const char *port, const char *map_cfg_file,
                          const char *entities_cfg_file);

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
  std::vector<ThreadSafeQueue<Command *> *> queues_commands;
  Socket server_socket;
  std::list<ClientHandler *> clients;
  StartingInfoNotification *create_start_notification(unsigned int hero_id);
  /*Remueve a los clientes del vector clients
   que hayan muerto o hayan terminado de jugar
  */
  void garbage_collector();
};

#endif  // CLIENTLISTENER_H
