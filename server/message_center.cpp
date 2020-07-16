#include "message_center.h"

MessageCenter::MessageCenter() : mutex() {}

MessageCenter::~MessageCenter() {}

void MessageCenter::add_player(
    std::string player_name,
    BlockingThreadSafeQueue<Notification *> *notification_queue) {
  std::unique_lock<std::mutex> lock(mutex);
  players_notification_queues.emplace(player_name, notification_queue);
}
void MessageCenter::remove_player(std::string player_name) {
  std::unique_lock<std::mutex> lock(mutex);
  if (players_notification_queues.count(player_name) < 1) return;
  players_notification_queues.erase(player_name);
}

void MessageCenter::notify_error(std::string player, std::string error) {
  std::unique_lock<std::mutex> lock(mutex);
  if (players_notification_queues.count(player) < 1) return;
  send_message(player, error);
}

void MessageCenter::notify_waiting_time_to_revive(std::string dst,
                                                  unsigned int seconds) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string msg = "Por favor, espera " + std::to_string(seconds) +
                    " segundos para revivir.";
  send_message(dst, msg);
}

// Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a
// ser enviada a player_dst
void MessageCenter::send_message(std::string dst, std::string message) {
  try {
    BlockingThreadSafeQueue<Notification *> *q =
        players_notification_queues.at(dst);
    if (!q) return;
    std::vector<unsigned char> notification;
    uint8_t notification_id = 4;
    uint8_t message_length = message.length();
    notification.push_back(notification_id);
    notification.push_back(message_length);
    notification.insert(notification.end(), message.begin(), message.end());
    MessageNotification *message_notification =
        new MessageNotification(notification);
    q->push(message_notification);
  } catch (const std::out_of_range &oor) {
    std::cout << "out of range at message center " << dst << std::endl;
  }
}

void MessageCenter::notify_damage_received(std::string attacked,
                                           unsigned int dmg,
                                           std::string attacker) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message =
      "Recibiste " + std::to_string(dmg) + " de daño de: " + attacker;
  if (dmg == 0) {
    message = "Bloqueaste el ataque de " + attacker + "!";
  }
  send_message(attacked, message);
}

void MessageCenter::send_private_message(std::string src, std::string dst,
                                         std::string message) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string msg = src + ": " + message;
  send_message(dst, msg);
}

void MessageCenter::notify_cant_attack_low_levels(std::string attacker,
                                                  std::string attacked,
                                                  int attacked_level,
                                                  int newbie_level_cap) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string msg;
  if (attacked_level < newbie_level_cap) {
    msg = "No podes atacar a jugadores inferiores a nivel 10, " + attacked +
          " es nivel " + std::to_string(attacked_level);
  } else {
    msg = "Hay mucha diferencia de niveles entre vos y " + attacked +
          ", es nivel " + std::to_string(attacked_level) +
          ". No podes hacerle daño.";
  }
  send_message(attacker, msg);
}

void MessageCenter::send_inventory_is_full_message(std::string dst) {
  std::string msg = "Inventario lleno!";
  send_message(dst, msg);
}

void MessageCenter::notify_cant_change_map(std::string player) {
  std::string msg = "Espera unos segundos para poder volver a cambiar de mapa!";
  send_message(player, msg);
}

void MessageCenter::notify_need_to_be_close_to_npc_to_buy_or_sell(
    std::string player) {
  std::string msg =
      "Para hacer eso tenes que estar cerca de un sacerdote o un comerciante!";
  send_message(player, msg);
}
void MessageCenter::notify_no_npc_to_sell_item(std::string player) {
  std::string msg = "No podes vender ese item a este NPC!";
  send_message(player, msg);
}

// void MessageCenter::notify_must_be_close_to_banker(std::string player) {
//   std::string msg = "Tenes que estar cerca de un banquero para ejecutar este comando!";
//   send_message(player, msg);
// }

void MessageCenter::notify_no_npc_to_buy_item(std::string player) {
  std::string msg = "No podes comprar ese item a este NPC!";
  send_message(player, msg);
}

void MessageCenter::notify_need_to_be_close_to_npc(std::string player) {
  std::string msg =
      "Tenes que estar cerca del NPC para ejecutar este comando!";
  send_message(player, msg);
}

void MessageCenter::notify_cant_sell_not_existing_item(std::string player) {
  std::string msg = "No podes vender un item que no tengas en tu inventario!";
  send_message(player, msg);
}

void MessageCenter::notify_ghosts_cant_buy_items(std::string player) {
  std::string msg = "Los fantasmas no pueden comprar ni vender items!";
  send_message(player, msg);
}

void MessageCenter::send_not_enough_gold_message(std::string dst,
                                                 unsigned int price) {
  std::string msg = "Dinero insuficiente! El costo del objeto es " +
                    std::to_string(price) + " monedas";
  send_message(dst, msg);
}

void MessageCenter::notify_damage_done(std::string attacker, unsigned int dmg,
                                       std::string attacked) {
  std::unique_lock<std::mutex> lock(mutex);
  std::string message =
      "Has causado " + std::to_string(dmg) + " de daño a " + attacked;
  if (dmg == 0) message = attacker + " ha bloqueado tu ataque!";
  send_message(attacker, message);
}