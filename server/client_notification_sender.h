#ifndef CLIENT_NOTIFICATION_SENDER_H
#define CLIENT_NOTIFICATION_SENDER_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "argentum_game.h"
#include "common_socket.h"
#include "message_center.h"
#include "protocol.h"
#include "thread.h"

class ClientNotificationSender : public Thread {
 public:
  // Recibe los comandos del cliente y los encola para que el juego los procese
  ClientNotificationSender(
      Socket &peer_socket,
      BlockingThreadSafeQueue<Notification *> *notifications_queue,
      MessageCenter &message_center, const std::string &player_name);
  ~ClientNotificationSender() override;
  void run() override;
  bool is_alive();
  void stop();

 private:
  Socket &peer_socket;
  BlockingThreadSafeQueue<Notification *> *notifications_queue;
  bool alive;
  MessageCenter &message_center;
  std::string player_name;
};

#endif  // CLIENT_NOTIFICATION_SENDER_H
