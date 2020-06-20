#ifndef CLIENT_NOTIFICATION_SENDER_H
#define CLIENT_NOTIFICATION_SENDER_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "argentum_game.h"
#include "common_socket.h"
#include "protocol.h"
#include "thread.h"

class ClientNotificationSender : public Thread {
 public:
  //Recibe los comandos del cliente y los encola para que el juego los procese
  ClientNotificationSender(Socket &peer_socket, ArgentumGame *game);
  ~ClientNotificationSender() override;
  void run() override;
  bool is_alive();
  void stop();

 private:
  ArgentumGame *game;
  Socket &peer_socket;
  bool alive = true;
};

#endif  // CLIENT_NOTIFICATION_SENDER_H
