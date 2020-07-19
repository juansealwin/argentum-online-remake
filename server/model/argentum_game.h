#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H
#include <unistd.h>

#include <fstream>
#include <mutex>
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "../util/thread.h"
#include "../util/thread_safe_queue.h"
#include "bank_status_notification.h"
#include "banker.h"
#include "base_character.h"
#include "command.h"  //<- guarda con esto y dependencias circulares
#include "drop.h"
#include "drops_manager.h"
#include "files_handler.h"
#include "game_status_notification.h"
#include "hero.h"
#include "heroes_manager.h"
#include "map.h"
#include "merchant.h"
#include "message_center.h"
#include "monster.h"
#include "monsters_manager.h"
#include "move_command.h"
#include "priest.h"
#include "projectile.h"
#include "projectiles_manager.h"
#include "sale_info_notification.h"
#include "serializer.h"

typedef enum { PRIEST = 33, MERCHANT, BANKER } npc_t;
// #define PRIEST 33
// #define MERCHANT 34
// #define BANKER 35

class ArgentumGame : public Thread {
 public:
  // Instancia una nueva sala de Argentum
  ArgentumGame(const unsigned int room,
               ThreadSafeQueue<Command *> *commands_queue, Json::Value &map_cfg,
               std::ifstream &entities_config, unsigned int &entities_ids,
               MessageCenter &message_center, FilesHandler &files_handler);
  ~ArgentumGame() override;
  void run() override;
  unsigned int get_room();
  void kill();
  void print_debug_map();
  void hero_dequip_item(int entity_id, int item_id);
  // equipa o usa una pocion
  void hero_use_special(int entity_id);
  void hero_revive(int entity_id);
  void hero_heal(int entity_id);
  void hero_buy_item(int entity_id, int item_id);
  void hero_sell_item(int entity_id, int item_id);
  void hero_use_item(int entity_id, int item_id);
  void hero_drop_item(int entity_id, int item_id);
  void hero_bank_item(int entity_id, int item_id);
  void hero_unbank_item(int entity_id, int item_id);
  void hero_bank_gold(int entity_id, int ammount);
  void hero_unbank_gold(int entity_id, int ammount);
  void hero_meditate(int entity_id);
  // envia una notificacion al cliente del estado del banco o
  // de lo que venda el merchant/priest mas cercano
  void hero_get_closest_npc_info(int entity_id);
  void set_hero_speed(int entity_id, int speed_x, int speedy);
  void throw_projectile(int attacker_id);
  void pick_up_drop(unsigned int player_id);
  // Settea a un jugador como muerto para que sea removido durante el update()
  void kill_player(unsigned int player_id);

  // devuelve el id auto-generado
  unsigned int add_new_hero(const std::string &hero_race,
                            const std::string &hero_class,
                            const std::string &hero_name);
  void add_existing_hero(Hero *hero, unsigned int id);
  void add_notification_queue(BlockingThreadSafeQueue<Notification *> *queue,
                              unsigned int player_id);
  // remueve colas de notificaciones para no notificar a clientes meurtos
  void clean_notifications_queues();
  // remueve y devuelve el heroe y su cola de notificaciones asociada
  std::tuple<Hero *, BlockingThreadSafeQueue<Notification *> *>
  remove_hero_and_notification_queue(int player_id);
  friend class Serializer;
  ThreadSafeQueue<Command *> *get_commands_queue();
  void stop_notification_queue(int player_id);
  void send_message(unsigned int player_id, std::string dst, std::string msg);
  FilesHandler &files_handler;
  Hero *get_hero_by_id(const int id);

 private:
  unsigned int room = 0;
  // A esta cola deberian tener acceso tambien los clientes conectados a esta
  // sala, cuando envian un comando nuevo se encolan y en cada update() del
  // juego se van procesando
  ThreadSafeQueue<Command *> *commands_queue;
  std::mutex mutex;
  std::string map_name;
  Map *map;
  bool alive = true;
  unsigned int &entities_ids;
  MessageCenter &message_center;
  // actualiza el mundo segun los comandos recibidos
  // si recibe true, ademas,  aplica los cambios que se deberian aplicar pasado
  // un segundo
  void update();
  void remove_death_entities();
  // segun los ids de la capa 2 del json generado por tiled,
  // coloca a los monstruos iniciales del mapa.
  void place_initial_npcs(Json::Value &map_cfg);
  std::map<unsigned int, Entity *> npcs;
  std::map<unsigned int, Hero *> heroes;
  std::map<unsigned int, Monster *> monsters;
  std::map<unsigned int, Projectile *> projectiles;
  std::map<std::tuple<unsigned int, unsigned int>, Drop *> drops;
  std::map<std::tuple<unsigned int, unsigned int>, int> npc_positions;

  void send_game_status();
  Json::Value entities_cfg;
  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>
      queues_notifications;
  std::tuple<unsigned int, unsigned int> get_contiguous_position(
      BaseCharacter *character);
  // agrega heroe en posicion x,y (los ejes estan invertidos)
  unsigned int place_hero(const std::string &hero_race,
                          const std::string &hero_class,
                          const std::string &hero_name, const unsigned int x,
                          const unsigned int y);
  void tests_proyectiles();
  void tests_drops();
  npc_t find_closest_npc();
  BankStatusNotification *get_bank_status(Hero *h);
  SaleInfoNotification *get_sale_info(npc_t npc);
  // devuelve true si hay un banker a 1 de distancia
  bool is_npc_close(int x, int y, npc_t npc);
  std::tuple<int, int> get_npc_pos(npc_t npc);
  bool closest_npcs_sells_or_buys_item(int x, int y, item_t item);
  ProjectileManager projectile_manager;
  HeroesManager heroes_manager;
  MonstersManager monsters_manager;
  DropsManager drops_manager;
  std::vector<item_t> merchant_sale_items = {
      turtle_shield,  iron_shield,  hood,        iron_helmet, magic_hat,
      leather_armour, plate_armour, blue_tunic,  sword,       axe,
      hammer,         simple_bow,   compound_bow};

  std::vector<item_t> priest_sale_items = {hp_potion,   mana_potion,
                                           ash_stick,   gnarled_staff,
                                           crimp_staff, elven_flute};
};

#endif  // ARGENTUMGAME_H
