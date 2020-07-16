#ifndef MESSAGE_CENTER_H
#define MESSAGE_CENTER_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "../util/thread_safe_queue.h"
#include "message_notification.h"

class MessageCenter {
 public:
  MessageCenter();
  ~MessageCenter();
  void add_player(std::string player_name,
                  BlockingThreadSafeQueue<Notification *> *notification_queue);
  void remove_player(std::string player_name);
  // Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a
  // ser enviada a player_dst
  void notify_error(std::string player, std::string error);
  void notify_damage_done(std::string attacker, unsigned int dmg,
                          std::string attacked);
  void notify_damage_received(std::string attacked, unsigned int dmg,
                              std::string attacker);
  void send_private_message(std::string src, std::string dst,
                            std::string message);
  void send_inventory_is_full_message(std::string dst);
  void send_not_enough_gold_message(std::string dst, unsigned int price);
  void notify_waiting_time_to_revive(std::string dst, unsigned int seconds);
  void notify_cant_attack_low_levels(std::string attacker, std::string attacked,
                                     int attacked_level, int newbie_level_cap);
  void notify_cant_change_map(std::string player);
  void notify_cant_sell_not_existing_item(std::string player);
  void notify_need_to_be_close_to_npc_to_buy_or_sell(std::string player);
  void notify_need_to_be_close_to_npc(std::string player);
  void notify_no_npc_to_sell_item(std::string player);
  void notify_no_npc_to_buy_item(std::string player);
  void notify_ghosts_cant_buy_items(std::string player);
  //void notify_must_be_close_to_banker(std::string player);

 private:
  // mapea nombre del jugador con su cola
  void send_message(std::string dst, std::string message);
  std::mutex mutex;
  std::map<std::string, BlockingThreadSafeQueue<Notification *> *>
      players_notification_queues;
};

#endif  // MESSAGE_CENTER_H
