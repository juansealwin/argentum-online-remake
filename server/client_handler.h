#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "argentum_game.h"
#include "common_socket.h"
#include "protocol.h"
#include "thread.h"
#include "client_command_receiver.h"
#include "client_notification_sender.h"

class ClientHandler {//: public Thread {
 public:
  // Instancia un nuevo manejador de clientes para que juege
  // a el juego ArgentumGame recibido por parametro (Es la sala)
  ClientHandler(Socket socket, ArgentumGame *game);
  ~ClientHandler();
  //void run() override;
  // Devuelve True mientras el juego siga en curso
  bool is_alive();

 private:
  ClientCommandReceiver *receiver;
  ClientNotificationSender *sender;
  ArgentumGame *game;
  Socket peer_socket;
  bool alive = true;
};

#endif  // CLIENTHANDLER_H
