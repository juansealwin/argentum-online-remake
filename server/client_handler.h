#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "argentum_game.h"
#include "client_command_receiver.h"
#include "client_notification_sender.h"
#include "common_socket.h"
#include "protocol.h"
#include "thread.h"
#include "message_center.h"
class ClientHandler {  //: public Thread {
 public:
  // Instancia un nuevo manejador de clientes para que juege
  // a el juego ArgentumGame recibido por parametro (Es la sala)
  ClientHandler(Socket socket, unsigned int game_room,
                ThreadSafeQueue<Command *> *commands_queue,
                BlockingThreadSafeQueue<Notification *> *notifications_queue,
                unsigned int hero_id, std::vector<ArgentumGame *> &games,
                std::string player_name, MessageCenter &message_center);
  ClientHandler(const ClientHandler &c2) = delete;
  ~ClientHandler();
  // void run() override;
  // Devuelve True mientras el juego siga en curso
  bool is_alive();

 private:
  ClientCommandReceiver *receiver;
  ClientNotificationSender *sender;
  BlockingThreadSafeQueue<Notification *> *notifications_queue;
  ThreadSafeQueue<Command *> *commands_queue;
  Socket peer_socket;
  bool alive = true;
  //std::string player_name;
  //MessageCenter &message_center;
};

#endif  // CLIENTHANDLER_H
