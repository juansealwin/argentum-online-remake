#include "message_center.h"

MessageCenter::MessageCenter() : mutex() {}

MessageCenter::~MessageCenter() {}

void MessageCenter::add_player(std::string player_name, BlockingThreadSafeQueue<Notification *> *notification_queue) {
  std::unique_lock<std::mutex> lock(mutex);
  //std::cout << "added player with name: " << player_name << std::endl;
  players_notification_queues.emplace(player_name, notification_queue);
}
void MessageCenter::remove_player(std::string player_name) {
  std::unique_lock<std::mutex> lock(mutex);
  //std::cout << "removing player with name: " << player_name << std::endl;
  if (players_notification_queues.count(player_name) > 0) {
    players_notification_queues.erase(player_name);
  }
}
  //Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a ser enviada a player_dst
void MessageCenter::send_message(std::string dst, std::string message) {
  BlockingThreadSafeQueue<Notification *> *q = players_notification_queues.at(dst);
  if(!q) return;
  std::vector<unsigned char> notification;
  // std::vector<unsigned char>::iterator it;
  // mover a la clase
  uint8_t notification_id = 4;
  uint8_t message_length = message.length();
  notification.push_back(notification_id);
  notification.push_back(message_length);
  // it = notification.end();
  notification.insert(notification.end(), message.begin(), message.end());
  MessageNotification *message_notification = new MessageNotification(notification);
  q->push(message_notification);
}

void MessageCenter::notify_damage_received(std::string attacked, unsigned int dmg, std::string attacker) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message = "Damage received: " + std::to_string(dmg) + " from " + attacker;
  if (dmg == 0) {
   message = "Blocked attack from " + attacker + "!";
  }
  //BlockingThreadSafeQueue<Notification *> *q = players_notification_queues.at(attacked);
  send_message(attacked, message);
  // if(q) {
  //std::cout << "Sending message: " << message << std::endl;
  // }
}

void MessageCenter::send_private_message(std::string src, std::string dst, std::string message) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string msg = dst + ": " + message;
  //std::cout << "destination is " << dst << std::endl;
  send_message(dst, msg);
}

void MessageCenter::send_inventory_is_full_message(std::string dst) {
  std::string msg = "Inventario lleno!";
  send_message(dst, msg);
}

void MessageCenter::send_not_enough_gold_message(std::string dst, unsigned int price) {
  std::string msg = "Dinero insuficiente! El costo del objeto es " + std::to_string(price) + " monedas";
  send_message(dst, msg);
}

  
void MessageCenter::notify_damage_done(std::string attacker, unsigned int dmg, std::string attacked) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message = "Damage done: " + std::to_string(dmg) + " to " + attacked;
  if (dmg == 0) {
   message = attacker + " blocked your attack!";
  }
  send_message(attacker, message);

  //BlockingThreadSafeQueue<Notification *> *q = players_notification_queues.at(attacker);
  // if(q) {
  //   std::cout << "Sending message: " << message << std::endl;
  // }

}