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

void MessageCenter::notify_damage_received(std::string attacked, unsigned int dmg, std::string attacker) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message = "Damage received: " + std::to_string(dmg) + " from " + attacker;
  if (dmg == 0) {
   message = "Blocked attack from " + attacker + "!";
  }
  BlockingThreadSafeQueue<Notification *> *q = players_notification_queues.at(attacked);
  if(q) {
      std::cout << "Sending message: " << message << std::endl;
  }
}

  
void MessageCenter::notify_damage_done(std::string attacker, unsigned int dmg, std::string attacked) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message = "Damage done: " + std::to_string(dmg) + " to " + attacked;
  if (dmg == 0) {
   message = attacker + " blocked your attack!";
  }
  BlockingThreadSafeQueue<Notification *> *q = players_notification_queues.at(attacker);
  if(q) {
    std::cout << "Sending message: " << message << std::endl;
  }

}