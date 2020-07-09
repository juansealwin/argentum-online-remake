#ifndef CLIENT_COMMAND_RECEIVER_H
#define CLIENT_COMMAND_RECEIVER_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "argentum_game.h"
#include "command_blocker.h"
#include "command_factory.h"
#include "common_socket.h"
#include "protocol.h"
#include "thread.h"
#include "change_game_room_dto.h"
#include "quit_command_dto.h"

class ClientCommandReceiver : public Thread {
 public:
  // Recibe los comandos del cliente y los encola para que el juego los procese
  ClientCommandReceiver(Socket &peer_socket, unsigned int game_room,
                        ThreadSafeQueue<Command *> *commands_queue,
                        unsigned int hero_id,
                        std::vector<ArgentumGame *> &game_rooms);
  ~ClientCommandReceiver() override;
  void run() override;
  bool is_alive();
  void stop();

 private:
  
  Socket &peer_socket;
  unsigned int current_game_room;
  ThreadSafeQueue<Command *> *commands_queue;
  unsigned int hero_id;
  bool alive;
  std::vector<ArgentumGame *> game_rooms;
  CommandBlocker command_blocker;
  //transfiere al heroe y su cola de notificaciones a la nueva sala
  //tambien cambia la referencia de la cola de comandos
  void change_game_room(unsigned int new_game_room);
 
};

#endif  // CLIENT_COMMAND_RECEIVER_H
