#include "argentum_game.h"

#include <iostream>

#include "defensive_item.h"
#include "weapon.h"
ArgentumGame::ArgentumGame(
    const unsigned int room_number, ThreadSafeQueue<Command *> *commands_queue,
    Json::Value &map_cfg, std::ifstream &entities_config,
    unsigned int &entities_ids, MessageCenter &message_center,
    FilesHandler &files_handler,
    BlockingThreadSafeQueue<
        std::tuple<std::string, std::vector<unsigned char>> *>
        *players_serializations_queue)
    : 
      files_handler(files_handler),
      room(room_number),
      commands_queue(commands_queue),
      mutex(),
      alive(true),
      entities_ids(entities_ids),
      message_center(message_center),
      players_serializations_queue(players_serializations_queue) {
  std::unique_lock<std::mutex> lock(mutex);
  entities_config >> entities_cfg;
  map = new Map(map_cfg);
  map_name = map_cfg["editorsettings"]["export"]["target"].asString();
  std::cout << "New game in " << map_name << std::endl;
  place_initial_npcs(map_cfg);
}

void ArgentumGame::place_initial_npcs(Json::Value &map_cfg) {
  int row = 0;
  int col = 0;
  int map_cols = map_cfg["width"].asInt();
  for (const auto &jv : map_cfg["layers"][1]["data"]) {
    Entity *e = nullptr;
    int type = jv.asInt();
    std::tuple<unsigned int, unsigned int> pos =
        std::tuple<unsigned int, unsigned int>(row, col);
    if (type == PRIEST) {
      e = new Priest(entities_ids, row, col, type, 'p');
      npc_positions.emplace(pos, PRIEST);
    } else if (type == MERCHANT) {
      npc_positions.emplace(pos, MERCHANT);
      e = new Merchant(entities_ids, row, col, type, 'm');
    } else if (type == BANKER) {
      npc_positions.emplace(pos, BANKER);
      e = new Banker(entities_ids, row, col, type, 'b');
    }
    if (e) {
      map->ocupy_cell(row, col, entities_ids);
      npcs.emplace(entities_ids++, e);
    }
    col++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
}

/*********************** Acciones personajes *************************/

void ArgentumGame::hero_level_up(int entity_id) {
  Hero *hero = nullptr;
  try {
    hero = heroes.at(entity_id);
    hero->level_up();
  } catch (ModelException &e) {
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_use_special(int entity_id) {
  Hero *hero = nullptr;
  try {
    hero = heroes.at(entity_id);
    hero->use_special_staff();
  } catch (ModelException &e) {
    if (hero) message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}
void ArgentumGame::hero_revive(int entity_id) {
  Hero *hero = nullptr;
  try {
    hero = heroes.at(entity_id);
    if (!is_npc_close(hero->x_position, hero->y_position, PRIEST)) {
      std::tuple<unsigned int, unsigned int> pos = get_npc_pos(PRIEST);
      int x = std::get<0>(pos);
      int y = std::get<1>(pos);
      if (x == -1) {
        message_center.notify_error(hero->name,
                                    "Tenes que moverte a un mapa con un cura!");
        return;
      }
      int distance =
          HelperFunctions::distance(hero->x_position, x, hero->y_position, y);
      int seconds_blocked = ((distance / 3) + 10) / 2;
      hero->block(seconds_blocked, x + 1, y);
      message_center.notify_waiting_time_to_revive(hero->name, seconds_blocked);
    } else
      hero->revive();
  } catch (ModelException &e) {
    if (hero) message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}
void ArgentumGame::hero_heal(int entity_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    if (!is_npc_close(hero->x_position, hero->y_position, PRIEST)) return;
    hero->affected_by = elven_flute;
    hero->heal(entities_cfg["npcs"]["priest"]["hpRegen"].asUInt(),
               entities_cfg["npcs"]["priest"]["manaRegen"].asUInt());
  } catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_meditate(int entity_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    hero->meditate();
  } catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_buy_item(int entity_id, int item_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    if ((is_npc_close(hero->x_position, hero->y_position, MERCHANT)) +
            (is_npc_close(hero->x_position, hero->y_position, PRIEST)) <
        1) {
      message_center.notify_need_to_be_close_to_npc_to_buy_or_sell(hero->name);
      return;
    }
    if (hero->is_death()) {
      message_center.notify_ghosts_cant_buy_items(hero->name);
      return;
    }
    if (hero->inventory->is_full()) {
      message_center.send_inventory_is_full_message(hero->name);
      return;
    }
    if (!closest_npcs_sells_or_buys_item(hero->x_position, hero->y_position,
                                         (item_t)item_id)) {
      message_center.notify_no_npc_to_buy_item(hero->name);
      return;
    };
    unsigned int item_price =
        ItemFactory::get_item_price(entities_cfg["items"], (item_t)item_id);
    if (!hero->has_gold(item_price)) {
      message_center.send_not_enough_gold_message(hero->name, item_price);
      return;
    }

    hero->remove_gold(item_price);
    Item *i = ItemFactory::create_item(entities_cfg["items"], (item_t)item_id);
    hero->add_item(i);
  } catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_sell_item(int entity_id, int item_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    if ((is_npc_close(hero->x_position, hero->y_position, MERCHANT)) +
            (is_npc_close(hero->x_position, hero->y_position, PRIEST)) <
        1) {
      message_center.notify_need_to_be_close_to_npc_to_buy_or_sell(hero->name);
      return;
    }
    if (hero->is_death()) {
      message_center.notify_ghosts_cant_buy_items(hero->name);
      return;
    }
    if (!hero->inventory->has_item(item_id)) {
      message_center.notify_cant_sell_not_existing_item(hero->name);
      return;
    }
    if (!closest_npcs_sells_or_buys_item(hero->x_position, hero->y_position,
                                         (item_t)item_id)) {
      message_center.notify_no_npc_to_sell_item(hero->name);
      return;
    };
    unsigned int item_price =
        ItemFactory::get_item_price(entities_cfg["items"], (item_t)item_id);
    if (hero->gold_space_remaining() < item_price) return;
    Item *i = hero->remove_item(item_id);
    hero->add_gold(item_price);
    delete i;
  } catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_bank_item(int entity_id, int item_id) {
  Hero *hero = nullptr;

  try {
    hero = heroes.at(entity_id);

    if (!is_npc_close(hero->x_position, hero->y_position, BANKER)) {
      // message_center.notify_must_be_close_to_banker(hero->name);
      return;
    }
    hero->bank_item(item_id);
  } catch (ModelException &e) {
    if (hero) message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_unbank_item(int entity_id, int item_id) {
  Hero *hero = nullptr;

  try {
    hero = heroes.at(entity_id);

    if (!is_npc_close(hero->x_position, hero->y_position, BANKER)) {
      // message_center.notify_must_be_close_to_banker(hero->name);
      return;
    }
    hero->unbank_item(item_id);

  } catch (ModelException &e) {
    if (hero) message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_bank_gold(int entity_id, int ammount) {
  Hero *hero = nullptr;

  try {
    hero = heroes.at(entity_id);
    if (!is_npc_close(hero->x_position, hero->y_position, BANKER)) {
      // message_center.notify_must_be_close_to_banker(hero->name);
      return;
    }
    hero->bank_gold(ammount);

  } catch (ModelException &e) {
    if (hero) message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_unbank_gold(int entity_id, int ammount) {
  Hero *hero = nullptr;

  try {
    hero = heroes.at(entity_id);

    if (!is_npc_close(hero->x_position, hero->y_position, BANKER)) {
      // message_center.notify_must_be_close_to_banker(hero->name);
      return;
    }
    hero->unbank_gold(ammount);

  } catch (ModelException &e) {
    message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}
void ArgentumGame::hero_get_closest_npc_info(int entity_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    Notification *n = nullptr;
    if (is_npc_close(hero->x_position, hero->y_position, BANKER)) {
      n = get_bank_status(hero);

    } else if (is_npc_close(hero->x_position, hero->y_position, MERCHANT)) {
      n = get_sale_info(MERCHANT);
    } else if (is_npc_close(hero->x_position, hero->y_position, PRIEST)) {
      n = get_sale_info(PRIEST);
    } else {
      message_center.notify_need_to_be_close_to_npc(hero->name);
      return;
    }
    hero->set_close_to_npc(true);
    BlockingThreadSafeQueue<Notification *> *q =
        queues_notifications.at(entity_id);
    q->push(n);
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_drop_item(int entity_id, int item_id) {
  using namespace std;
  try {
    Hero *hero = heroes.at(entity_id);
    Item *i = hero->remove_item(item_id);
    tuple<unsigned int, unsigned int> pos =
        tuple<unsigned int, unsigned int>(hero->x_position, hero->y_position);
    drops_manager.add_drop(std::ref(drops), i, pos,
                           std::ref(entities_cfg["items"]), entities_ids);
  } catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_dequip_item(int entity_id, int item_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    hero->unequip(item_id);
  }

  catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::hero_use_item(int entity_id, int item_id) {
  try {
    Hero *hero = heroes.at(entity_id);
    hero->use_item(item_id);
  }

  catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::set_hero_speed(int entity_id, int speed_x, int speed_y) {
  try {
    Hero *hero = heroes.at(entity_id);
    if (hero->blocked) return;
    hero->set_speed_x(speed_x);
    hero->set_speed_y(speed_y);
    hero->set_close_to_npc(false);
    hero->meditating = false;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::throw_projectile(int attacker_id) {
  Hero *hero = nullptr;
  try {
    hero = heroes.at(attacker_id);
    if (map->tile_is_safe(hero->x_position, hero->y_position)) return;
    // manejar errores despues
    // errores del heroe, y de posicion contigua inaccesible
    Attack attack_info = hero->attack();
    if (attack_info.attacker_weapon_range == 0) return;
    std::tuple<unsigned int, unsigned int> projectile_position =
        get_contiguous_position(hero);
    unsigned int x = std::get<0>(projectile_position);
    unsigned int y = std::get<1>(projectile_position);
    Projectile *projectile = new Projectile(
        entities_ids, x, y, attack_info.attacker_weapon_id, 'p',
        attack_info.damage, attack_info.critical, attacker_id,
        attack_info.attacker_weapon_range, hero->orientation, map);
    projectiles.emplace(entities_ids++, projectile);
  }

  catch (ModelException &e) {
    if (hero) message_center.notify_error(hero->name, e.what());
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::pick_up_drop(unsigned int player_id) {
  Hero *hero = heroes.at(player_id);

  try {
    std::tuple<unsigned int, unsigned int> pos =
        std::tuple<unsigned int, unsigned int>(hero->x_position,
                                               hero->y_position);
    if (drops.count(pos) == 0) return;
    Drop *drop = drops.at(pos);
    hero->pick_up_drop(drop);
  }

  catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::send_message(unsigned int player_id, std::string dst,
                                std::string msg) {
  try {
    Hero *hero = heroes.at(player_id);
    message_center.send_private_message(hero->get_name(), dst, msg);
  } catch (const std::out_of_range &oor) {
  }
}

void ArgentumGame::kill_player(unsigned int player_id) {
  // bloque try por si crashea cliente
  try {
    Hero *hero = heroes.at(player_id);
    hero->alive = false;
  } catch (const std::exception &ex) {
  }
}

/*********************** Fin acciones personajes *********************/

std::tuple<Hero *, BlockingThreadSafeQueue<Notification *> *>
ArgentumGame::remove_hero_and_notification_queue(int player_id) {
  std::unique_lock<std::mutex> lock(mutex);
  std::map<unsigned int, Hero *>::iterator it_heroes;
  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>::iterator
      it_queues;
  it_heroes = heroes.find(player_id);
  it_queues = queues_notifications.find(player_id);
  Hero *hero = it_heroes->second;
  map->empty_cell(hero->x_position, hero->y_position);
  BlockingThreadSafeQueue<Notification *> *q = it_queues->second;
  heroes.erase(player_id);
  queues_notifications.erase(player_id);
  return std::tuple<Hero *, BlockingThreadSafeQueue<Notification *> *>(hero, q);
}

unsigned int ArgentumGame::add_new_hero(const std::string &hero_race,
                                        const std::string &hero_class,
                                        const std::string &hero_name) {
  std::unique_lock<std::mutex> lock(mutex);
  std::tuple<int, int> free_tile = map->get_random_free_space();
  int x = std::get<0>(free_tile);
  int y = std::get<1>(free_tile);

  Hero *hero = files_handler.get_player_status(
      hero_name, entities_cfg, entities_ids, x, y, std::ref(map));
  unsigned int new_player_id = 0;
  if (hero != nullptr) {
    new_player_id = place_existing_hero(hero, x, y);
  } else {
    new_player_id = place_hero(hero_race, hero_class, hero_name, x, y);
  }

  return new_player_id;
}

void ArgentumGame::add_existing_hero(Hero *hero, unsigned int id) {
  std::unique_lock<std::mutex> lock(mutex);
  std::tuple<int, int> free_tile = map->get_random_free_space();
  int x = std::get<0>(free_tile);
  int y = std::get<1>(free_tile);
  hero->set_position(x, y);
  // map->debug_print();
  hero->set_map(map);
  map->ocupy_cell(x, y, id);
  heroes.emplace(id, hero);
}

void ArgentumGame::kill() {
  std::unique_lock<std::mutex> lock(mutex);
  alive = false;
}

bool ArgentumGame::is_alive() {
  std::unique_lock<std::mutex> lock(mutex);
  return alive;
}

void ArgentumGame::update() {
  std::unique_lock<std::mutex> lock(mutex);
  while (!commands_queue->is_empty()) {
    Command *cmd = commands_queue->pop();
    cmd->execute(this);
    delete cmd;
  }
  // actualizar monstruos antes que heroes ya que pueden atacarlos y matarlos
  // creando drops
  monsters_manager.update(std::ref(monsters), std::ref(heroes), message_center,
                          entities_cfg);
  monsters_manager.respawn_monsters(
      std::ref(monsters), map, entities_cfg["monstersPoblation"].asUInt(),
      std::ref(entities_cfg["npcs"]), entities_ids);

  heroes_manager.update(
      std::ref(heroes),
      entities_cfg["milisecondsForRegeneratingHero"].asUInt() * 1000000,
      entities_cfg["milisecondsForAutomoveHero"].asUInt() * 1000000);

  projectile_manager.update(std::ref(heroes), std::ref(monsters),
                            std::ref(projectiles), message_center,
                            entities_cfg);
  projectile_manager.remove_death_projectiles(std::ref(projectiles), map);
}

void ArgentumGame::remove_death_entities() {
  drops_manager.create_drops(std::ref(heroes), std::ref(monsters),
                             std::ref(drops), entities_cfg["items"],
                             entities_ids);
  heroes_manager.remove_death_heroes(std::ref(heroes), map);
  monsters_manager.remove_death_monsters(std::ref(monsters), map);
  drops_manager.remove_old_and_empty_drops(std::ref(drops));
}

void ArgentumGame::clear_heroes_effects() {
  heroes_manager.clear_effects(std::ref(heroes));
}

void ArgentumGame::run() {
  long time_step = 1000 / entities_cfg["ups"].asFloat();
  while (alive) {
    auto initial = std::chrono::high_resolution_clock::now();
    update();
    send_game_status();
    clear_heroes_effects();
    remove_death_entities();
    auto final = std::chrono::high_resolution_clock::now();
    auto loop_duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
    long sleep_time = time_step - loop_duration.count();
    if (sleep_time > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
  }
}

unsigned int ArgentumGame::get_room() { return room; }

void ArgentumGame::send_game_status() {
  if (heroes.size() == 0) return;
  std::unique_lock<std::mutex> lock(mutex);
  std::vector<unsigned char> game_status =
      Serializer::serialize_game_status(this);

  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>::iterator
      it;
  for (it = queues_notifications.begin(); it != queues_notifications.end();) {
    it->second->push(new GameStatusNotification(game_status));
    ++it;
  }
}

void ArgentumGame::add_notification_queue(
    BlockingThreadSafeQueue<Notification *> *queue, unsigned int player_id) {
  std::unique_lock<std::mutex> lock(mutex);
  queues_notifications.emplace(player_id, queue);
}

ThreadSafeQueue<Command *> *ArgentumGame::get_commands_queue() {
  return commands_queue;
}

void ArgentumGame::clean_notifications_queues() {
  // std::unique_lock<std::mutex> lock(mutex);
  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>::iterator
      it;
  for (it = queues_notifications.begin(); it != queues_notifications.end();) {
    if ((it->second)->is_closed()) {
      // std::cout << "cleaning notif q" << std::endl;
      it = queues_notifications.erase(it);

    } else
      ++it;
  }
}

/********************* metodos privados *****************************/

std::tuple<int, int> ArgentumGame::get_npc_pos(npc_t npc) {
  for (auto it = npc_positions.begin(); it != npc_positions.end(); ++it)
    if (it->second == npc) return it->first;
  return std::tuple<int, int>(-1, -1);
}

std::tuple<unsigned int, unsigned int> ArgentumGame::get_contiguous_position(
    BaseCharacter *character) {
  unsigned int x_pos = character->x_position;
  unsigned int y_pos = character->y_position;
  switch (character->orientation) {
    case (orientation_right):
      y_pos++;
      break;
    case (orientation_left):
      y_pos--;
      break;
    case (orientation_up):
      x_pos--;
      break;
    case (orientation_down):
      x_pos++;
      break;
  }
  return std::tuple<unsigned int, unsigned int>(x_pos, y_pos);
}
unsigned int ArgentumGame::place_hero(const std::string &hero_race,
                                      const std::string &hero_class,
                                      const std::string &hero_name,
                                      const unsigned int x,
                                      const unsigned int y) {
  Json::Value race_stats = entities_cfg["races"][hero_race];
  Json::Value class_stats = entities_cfg["classes"][hero_class];
  Hero *hero = new Hero(
      entities_ids, x, y, race_stats["id"].asUInt(), 'h',
      class_stats["level"].asUInt(),
      race_stats["strength"].asUInt() + class_stats["strength"].asUInt(),
      race_stats["intelligence"].asUInt() +
          class_stats["intelligence"].asUInt(),
      race_stats["agility"].asUInt() + class_stats["agility"].asUInt(),
      race_stats["constitution"].asUInt(), class_stats["fClassHp"].asUInt(),
      race_stats["fRaceHp"].asUInt(), race_stats["fRaceRecovery"].asUInt(),
      race_stats["fRaceMana"].asUInt(), class_stats["fClassMana"].asUInt(),
      class_stats["fClassMeditation"].asUInt(), race_stats["gold"].asUInt(),
      class_stats["id"].asUInt(), std::ref(map), hero_name,
      entities_cfg["criticalDamageMultiplier"].asFloat(),
      entities_cfg["inventorySize"].asInt(),
      entities_cfg["criticalDamageProbability"].asFloat(),
      entities_cfg["evasionProbability"].asFloat(),
      entities_cfg["maxSafeGoldMultiplier"].asFloat(),
      entities_cfg["levelUpLimitPower"].asFloat(),
      entities_cfg["startingXpCap"].asFloat(), entities_cfg["bankSize"].asInt(),
      entities_cfg["amountOfExperienceToUpdate"].asUInt(), true);
  setup_new_hero(hero);
  map->ocupy_cell(x, y, entities_ids);
  heroes.emplace(entities_ids, hero);
  return entities_ids++;
}

unsigned int ArgentumGame::place_existing_hero(Hero *hero, const unsigned int x,
                                               const unsigned int y) {
  map->ocupy_cell(x, y, entities_ids);
  heroes.emplace(entities_ids, hero);
  return entities_ids++;
}

void ArgentumGame::setup_new_hero(Hero *h) {
  std::vector<Item *> hero_items;
  switch (h->get_class_id()) {
    case mage:
      hero_items = setup_new_mage();
      break;

    case paladin:
      hero_items = setup_new_paladin();
      break;

    case warrior:
      hero_items = setup_new_warrior();
      break;

    case cleric:
      hero_items = setup_new_cleric();
      break;
    default:
      hero_items = setup_new_warrior();
      break;
  }
  for (auto &item : hero_items) {
    h->add_item(item);
  }
}

std::vector<Item *> ArgentumGame::setup_new_mage() {
  std::vector<Item *> mage_items;
  mage_items.push_back(ItemFactory::create_ash_stick(entities_cfg["items"]));
  mage_items.push_back(ItemFactory::create_blue_tunic(entities_cfg["items"]));
  mage_items.push_back(ItemFactory::create_magic_hat(entities_cfg["items"]));
  return mage_items;
}
std::vector<Item *> ArgentumGame::setup_new_paladin() {
  std::vector<Item *> paladin_items;
  paladin_items.push_back(
      ItemFactory::create_iron_shield(entities_cfg["items"]));
  paladin_items.push_back(
      ItemFactory::create_iron_helmet(entities_cfg["items"]));
  paladin_items.push_back(
      ItemFactory::create_plate_armour(entities_cfg["items"]));
  paladin_items.push_back(ItemFactory::create_sword(entities_cfg["items"]));
  return paladin_items;
}
std::vector<Item *> ArgentumGame::setup_new_cleric() {
  std::vector<Item *> cleric_items;
  cleric_items.push_back(
      ItemFactory::create_turtle_shield(entities_cfg["items"]));
  cleric_items.push_back(ItemFactory::create_blue_tunic(entities_cfg["items"]));
  cleric_items.push_back(ItemFactory::create_ash_stick(entities_cfg["items"]));
  return cleric_items;
}
std::vector<Item *> ArgentumGame::setup_new_warrior() {
  std::vector<Item *> warrior_items;
  warrior_items.push_back(
      ItemFactory::create_turtle_shield(entities_cfg["items"]));
  warrior_items.push_back(ItemFactory::create_hood(entities_cfg["items"]));
  warrior_items.push_back(
      ItemFactory::create_leather_armour(entities_cfg["items"]));
  warrior_items.push_back(ItemFactory::create_axe(entities_cfg["items"]));
  return warrior_items;
}

void ArgentumGame::print_debug_map() {
  std::unique_lock<std::mutex> lock(mutex);
  map->debug_print();
  std::cout << "\x1B[2J\x1B[H";
}

ArgentumGame::~ArgentumGame() {
  std::unique_lock<std::mutex> lock(mutex);
  for (auto &monster : monsters) {
    delete monster.second;
  }
  for (auto &hero : heroes) {
    delete hero.second;
  }
  for (auto &projectile : projectiles) {
    delete projectile.second;
  }
  for (auto &npc : npcs) {
    delete npc.second;
  }
  for (auto &drop : drops) {
    delete drop.second;
  }
  delete map;
  // Cierro cola y elimino comandos que no se podran procesar
  commands_queue->close();
  while (!commands_queue->is_empty()) {
    Command *cmd = commands_queue->pop();
    delete cmd;
  }
}

void ArgentumGame::stop_notification_queue(int player_id) {
  try {
    queues_notifications.at(player_id)->close();
  } catch (const std::exception &ex) {
  }
}

BankStatusNotification *ArgentumGame::get_bank_status(Hero *h) {
  std::vector<Item *> items = h->bank->items;
  uint8_t bank_size = items.size();
  std::vector<unsigned char> notification;
  uint8_t notification_id = 5;
  notification.push_back(notification_id);
  notification.push_back(bank_size);
  for (unsigned int i = 0; i < items.size(); i++) {
    uint8_t item_id = items.at(i)->id;
    notification.push_back(item_id);
  }
  uint16_t gold = h->bank->current_gold();
  unsigned int current_pos = notification.size();
  notification.resize(notification.size() + sizeof(gold));
  memcpy(notification.data() + current_pos, &gold, sizeof(gold));
  // mover a la clase
  BankStatusNotification *n = new BankStatusNotification(notification);
  return n;
}

bool ArgentumGame::is_npc_close(int x, int y, npc_t npc) {
  using namespace std;
  vector<tuple<int, int>> possible_spots = {
      tuple<int, int>(x + 1, y), tuple<int, int>(x - 1, y),
      tuple<int, int>(x, y + 1), tuple<int, int>(x, y - 1)};
  for (unsigned int j = 0; j < possible_spots.size(); j++) {
    int curr_x = get<0>(possible_spots.at(j));
    int curr_y = get<1>(possible_spots.at(j));
    tuple<int, int> pos = tuple<int, int>(curr_x, curr_y);
    if (npc_positions.count(pos) > 0) {
      if (npc_positions.at(pos) == npc) {
        return true;
      }
    }
  }
  return false;
}

SaleInfoNotification *ArgentumGame::get_sale_info(npc_t npc) {
  uint8_t notification_id = 6;
  std::vector<unsigned char> notification;
  notification.push_back(notification_id);
  std::vector<item_t> sale_items;
  if (npc == MERCHANT) {
    sale_items = merchant_sale_items;
  } else if (npc == PRIEST) {
    sale_items = priest_sale_items;
  }
  notification.push_back(sale_items.size());
  notification.insert(notification.end(), sale_items.begin(), sale_items.end());
  return new SaleInfoNotification(notification);
}

bool ArgentumGame::closest_npcs_sells_or_buys_item(int x, int y, item_t item) {
  if (is_npc_close(x, y, PRIEST)) {
    if ((std::count(priest_sale_items.begin(), priest_sale_items.end(), item)))
      return true;
  }
  if (is_npc_close(x, y, MERCHANT)) {
    if ((std::count(merchant_sale_items.begin(), merchant_sale_items.end(),
                    item)))
      return true;
  }
  return false;
}

Hero *ArgentumGame::get_hero_by_id(const int id) {
  return dynamic_cast<Hero *>(heroes.at(id));
}

void ArgentumGame::add_player_to_save(
    std::tuple<std::string, std::vector<unsigned char>> *player) {
  players_serializations_queue->push(player);
}
