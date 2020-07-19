#ifndef MESSAGE_CENTER_H
#define MESSAGE_CENTER_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "../util/thread_safe_queue.h"
#include "message_notification.h"

#define ENIE 241

class MessageCenter {
 public:
  MessageCenter();
  ~MessageCenter();
  void add_player(const std::string &player_name,
                  BlockingThreadSafeQueue<Notification *> *notification_queue);
  void remove_player(const std::string &player_name);
  // Agrega el nombre del origen al mensaje y crea una notificacion de mensaje a
  // ser enviada a player_dst
  void notify_error(const std::string &player, const std::string &error);
  void notify_damage_done(const std::string &attacker, const unsigned int dmg,
                          const std::string &attacked, bool attacked_was_death);
  void notify_damage_received(const std::string &attacked,
                              const unsigned int dmg,
                              const std::string &attacker,
                              bool attacked_was_death);
  void send_private_message(const std::string &src, const std::string &dst,
                            const std::string &message);
  void send_inventory_is_full_message(const std::string &dst);
  void send_not_enough_gold_message(const std::string &dst, unsigned int price);
  void notify_waiting_time_to_revive(const std::string &dst,
                                     unsigned int seconds);
  void notify_cant_attack_low_levels(const std::string &attacker,
                                     const std::string &attacked,
                                     int attacked_level, int newbie_level_cap);
  void notify_cant_change_map(const std::string &player);
  void notify_cant_sell_not_existing_item(const std::string &player);
  void notify_need_to_be_close_to_npc_to_buy_or_sell(const std::string &player);
  void notify_need_to_be_close_to_npc(const std::string &player);
  void notify_no_npc_to_sell_item(const std::string &player);
  void notify_no_npc_to_buy_item(const std::string &player);
  void notify_ghosts_cant_buy_items(const std::string &player);
  // void notify_must_be_close_to_banker(const std::string &player);

 private:
  // mapea nombre del jugador con su cola
  void send_message(const std::string &dst, const std::string &message);
  std::mutex mutex;
  std::map<std::string, BlockingThreadSafeQueue<Notification *> *>
      players_notification_queues;
};

#endif  // MESSAGE_CENTER_H
