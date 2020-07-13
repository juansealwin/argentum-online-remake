#include "message_center.h"

MessageCenter::MessageCenter() : mutex() {}

MessageCenter::~MessageCenter() {}

void MessageCenter::add_player(std::string player_name, BlockingThreadSafeQueue<Notification *> *notification_queue) {
  std::unique_lock<std::mutex> lock(mutex);
  players_notification_queues.emplace(player_name, notification_queue);
}
void MessageCenter::remove_player(std::string player_name) {
  std::unique_lock<std::mutex> lock(mutex);
  if (players_notification_queues.count(player_name) < 1) return;
  players_notification_queues.erase(player_name);
  
}
  //Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a ser enviada a player_dst
void MessageCenter::send_message(std::string dst, std::string message) {
  try {
  BlockingThreadSafeQueue<Notification *> *q = players_notification_queues.at(dst);
  if(!q) return;
  std::vector<unsigned char> notification;
  uint8_t notification_id = 4;
  uint8_t message_length = message.length();
  notification.push_back(notification_id);
  notification.push_back(message_length);
  notification.insert(notification.end(), message.begin(), message.end());
  MessageNotification *message_notification = new MessageNotification(notification);
  q->push(message_notification);
  }
  catch(const std::out_of_range& oor) {
    std::cout<< "out of range at message center " << dst << std::endl;
  }
}

void MessageCenter::notify_damage_received(std::string attacked, unsigned int dmg, std::string attacker) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message = "Has recibido " + std::to_string(dmg) + " de daño de: " + attacker;
  if (dmg == 0) {
   message = "Has bloqueado el ataque de " + attacker + "!";
  }
  send_message(attacked, message);
}

void MessageCenter::send_private_message(std::string src, std::string dst, std::string message) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string msg = src + ": " + message;
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
  std::string message = "Has causado " + std::to_string(dmg) + " de daño a " + attacked;
  if (dmg == 0) message = attacker + " ha bloqueado tu ataque!";
  send_message(attacker, message);

}