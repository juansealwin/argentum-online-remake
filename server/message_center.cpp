#include "message_center.h"

MessageCenter::MessageCenter() : mutex() {}

MessageCenter::~MessageCenter() {}

void MessageCenter::add_player(std::string player_name, BlockingThreadSafeQueue<Notification *> *notification_queue) {
  std::unique_lock<std::mutex> lock(mutex);
  std::cout << "added player with name: " << player_name << std::endl;
  players_notification_queues.emplace(player_name, notification_queue);
}
void MessageCenter::remove_player(std::string player_name) {
  std::unique_lock<std::mutex> lock(mutex);
  std::cout << "removing player with name: " << player_name << std::endl;
  if (players_notification_queues.count(player_name) > 0) {
    players_notification_queues.erase(player_name);
  }
}
  //Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a ser enviada a player_dst
void MessageCenter::send_message(std::string player_src, std::string player_dst, std::string message) {
  std::unique_lock<std::mutex> lock(mutex);
}
  