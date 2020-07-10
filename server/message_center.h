#ifndef MESSAGE_CENTER_H
#define MESSAGE_CENTER_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "../util/thread_safe_queue.h"

class MessageCenter {
 public:
  MessageCenter();
  ~MessageCenter();
  void add_player(std::string player_name,
                  BlockingThreadSafeQueue<Notification *> *notification_queue);
  void remove_player(std::string player_name);
  // Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a
  // ser enviada a player_dst
  void send_message(std::string player_src, std::string player_dst,
                    std::string message);

 private:
  // mapea nombre del jugador con su cola
  std::mutex mutex;
  std::map<std::string, BlockingThreadSafeQueue<Notification *> *>
      players_notification_queues;
};

#endif  // MESSAGE_CENTER_H
