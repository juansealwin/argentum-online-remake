#include "argentum_game.h"

#include <iostream>

#include "defensive_item.h"
#include "weapon.h"
ArgentumGame::ArgentumGame(const unsigned int room_number,
                           ThreadSafeQueue<Command *> *commands_queue,
                           Json::Value &map_cfg, std::ifstream &entities_config,
                           unsigned int &entities_ids)
    : room(room_number),
      commands_queue(commands_queue),
      mutex(),
      map(map_cfg),
      alive(true),
      entities_ids(entities_ids) {
  std::unique_lock<std::mutex> lock(mutex);
  // Json::Value map_cfg;
  // map_config >> map_cfg;
  entities_config >> entities_cfg;
  // map = new Map(map_cfg);
  this->map = Map(map_cfg);
  map_name = map_cfg["editorsettings"]["export"]["target"].asString();
  std::cout << "New game in " << map_name << std::endl;
  place_initial_npcs(map_cfg);
  tests_drops();
}
void ArgentumGame::tests_drops() {
  // std::cout << "testing drops" << std::endl;
  // Inventory *inventory = new Inventory(20);
  // inventory->add_item(new Item(8));
  // inventory->add_item(new Weapon(17, 4, 8, 5));
  // std::cout << "Inventory has item 17? " << inventory->has_item(17)
  //           << std::endl;
  // std::cout << "Inventory has item 8? " << inventory->has_item(8) <<
  // std::endl; Drop *drop = new Drop(34, inventory, 0); std::cout << "Is drop
  // empty?" << drop->is_empty() << std::endl; std::cout << "Inventory has item
  // 17? " << inventory->has_item(17)
  //           << std::endl;
  // std::cout << "Inventory has item 8? " << inventory->has_item(8) <<
  // std::endl; std::cout << "picking up first item" << std::endl; Item *item17
  // = drop->take_item(drop->size()); std::cout << "picking up second item" <<
  // std::endl; Item *item8 = drop->take_item(drop->size()); std::cout <<
  // "picked up items " << item17->id << ", " << item8->id
  //           << std::endl;
  // Inventory *inventory2 = new Inventory(25);
  // Drop *drop2 = new Drop(34, inventory2, 0);
  // std::cout << "Drop 2 is empty? " << drop2->is_empty() << std::endl;
  // delete drop2;
  // delete inventory2;
  // delete inventory;
  // delete drop;
  // delete item17;
  // delete item8;
}
void ArgentumGame::tests_proyectiles() {
  // std::cout << "Running tests" << std::endl;
  // place_hero("human", "warrior", "test_name1", 10, 23);
  // throw_projectile(15);
  // place_hero("human", "warrior", "test_name1", 0, 0);
  // place_hero("human", "warrior", "test_name1", 1, 0);
  // place_monster(2, 0);
  // throw_projectile(17);
  // throw_projectile(18);
  // place_hero("human", "warrior", "test_name1", 0, 3);
  // place_hero("human", "warrior", "test_name1", 5, 3);
  // throw_projectile(22);
  // throw_projectile(23);
  // place_monster(10, 3);
  // unsigned int hero1 = place_hero("human", "warrior", "test_name1", 99, 0);
  // unsigned int hero2 = place_hero("human", "warrior", "test_name1", 98, 1);
  // throw_projectile(hero1);
  // throw_projectile(hero2);
  // unsigned int hero3 = place_hero("human", "warrior", "test_name1", 5, 16);
  // unsigned int hero4 = place_hero("human", "warrior", "test_name1", 5, 16);
  // throw_projectile(hero3);
  // throw_projectile(hero4);
}

void ArgentumGame::place_initial_npcs(Json::Value &map_cfg) {
  int row = 0;
  int col = 0;
  int map_cols = map_cfg["width"].asInt();
  for (const auto &jv : map_cfg["layers"][2]["data"]) {
    Entity *e = nullptr;
    int type = jv.asInt();
    // en el futuro podria simplificarse, el caracter lo recibo para debug

    if (type == PRIEST) {
      e = new Priest(entities_ids, row, col, type, 'p');
    } else if (type == MERCHANT) {
      e = new Merchant(entities_ids, row, col, type, 'm');
    } else if (type == BANKER) {
      e = new Banker(entities_ids, row, col, type, 'b');
    }
    if (e) {
      map.ocupy_cell(row, col, entities_ids);
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

void ArgentumGame::hero_dequip_item(int entity_id, int item_id) {
  try {
    Hero *hero = dynamic_cast<Hero *>(heroes.at(entity_id));
    hero->unequip(item_id);
  }

  catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  }
}

void ArgentumGame::hero_use_item(int entity_id, int item_id) {
  try {
    Hero *hero = dynamic_cast<Hero *>(heroes.at(entity_id));
    hero->use_item(item_id);
  }

  catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  }
}

void ArgentumGame::move_entity(int entity_id, int x, int y) {
  BaseCharacter *character =
      dynamic_cast<BaseCharacter *>(heroes.at(entity_id));
  character->move(character->x_position + x, character->y_position + y);
}

void ArgentumGame::throw_projectile(int attacker_id) {
  Hero *hero = dynamic_cast<Hero *>(heroes.at(attacker_id));
  try {
    if (map.tile_is_safe(hero->x_position, hero->y_position)) return;
    // manejar errores despues
    // errores del heroe, y de posicion contigua inaccesible
    Attack attack_info = hero->attack();
    std::tuple<unsigned int, unsigned int> projectile_position =
        get_contiguous_position(hero);
    unsigned int x = std::get<0>(projectile_position);
    unsigned int y = std::get<1>(projectile_position);

    Projectile *projectile = new Projectile(
        entities_ids, x, y, attack_info.attacker_weapon_id, 'p',
        attack_info.damage, attack_info.critical, attacker_id,
        attack_info.attacker_weapon_range, hero->orientation, std::ref(map));
    projectiles.emplace(entities_ids++, projectile);
  }

  catch (ModelException &e) {
    std::cout << "Exception occured: " << e.what() << std::endl;
  }
}

void ArgentumGame::pick_up_drop(unsigned int player_id) {
  Hero *hero = dynamic_cast<Hero *>(heroes.at(player_id));

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
  }
}

void ArgentumGame::kill_player(unsigned int player_id) {
  Hero *hero = heroes.at(player_id);
  hero->alive = false;
}

/*********************** Fin acciones personajes *********************/

unsigned int ArgentumGame::add_new_hero(std::string hero_race,
                                        std::string hero_class,
                                        std::string hero_name) {
  std::tuple<int, int> free_tile = map.get_random_free_space();
  int x = std::get<0>(free_tile);
  int y = std::get<1>(free_tile);
  unsigned int new_player_id =
      place_hero(hero_race, hero_class, hero_name, x, y);
  return new_player_id;
}

void ArgentumGame::kill() {
  std::unique_lock<std::mutex> lock(mutex);
  alive = false;
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
  monsters_manager.update(std::ref(monsters), std::ref(heroes));
  monsters_manager.respawn_monsters(std::ref(monsters), std::ref(map), 20,
                                    std::ref(entities_cfg["npcs"]),
                                    entities_ids);

  heroes_manager.update(std::ref(heroes));

  projectile_manager.update(std::ref(heroes), std::ref(monsters),
                            std::ref(projectiles));
  projectile_manager.remove_death_projectiles(std::ref(projectiles),
                                              std::ref(map));
  drops_manager.create_drops(std::ref(heroes), std::ref(monsters),
                             std::ref(drops), entities_cfg["items"],
                             entities_ids);
  drops_manager.remove_old_and_empty_drops(std::ref(drops));
  heroes_manager.remove_death_heroes(std::ref(heroes), std::ref(map));
  monsters_manager.remove_death_monsters(std::ref(monsters), std::ref(map));
}

void ArgentumGame::run() {
  while (alive) {
    auto initial = std::chrono::high_resolution_clock::now();
    update();
    // print_debug_map();
    send_game_status();
    long time_step = 1000 / entities_cfg["ups"].asFloat();  // 60fps
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

std::vector<unsigned char> ArgentumGame::send_game_status() {
  std::unique_lock<std::mutex> lock(mutex);
  std::vector<unsigned char> game_status =
      Serializer::serialize_game_status_v3(this);

  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>::iterator
      it;
  for (it = queues_notifications.begin(); it != queues_notifications.end();) {
    it->second->push(new GameStatusNotification(game_status));
    ++it;
  }

  return game_status;
}

void ArgentumGame::add_notification_queue(
    BlockingThreadSafeQueue<Notification *> *queue, unsigned int player_id) {
  std::unique_lock<std::mutex> lock(mutex);
  // queues_notifications.push_back(queue);
  queues_notifications.emplace(player_id, queue);
}

void ArgentumGame::clean_notifications_queues() {
  // std::unique_lock<std::mutex> lock(mutex);
  // std::vector<BlockingThreadSafeQueue<Notification *> *>::iterator it;
  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>::iterator
      it;
  for (it = queues_notifications.begin(); it != queues_notifications.end();) {
    if ((it->second)->is_closed()) {
      Notification *n;
      while (!(it->second)->is_empty()) {
        n = (it->second)->pop();
        delete n;
      }
      delete (it->second);
      it = queues_notifications.erase(it);

    } else
      ++it;
  }
}

/********************* metodos privados *****************************/

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
unsigned int ArgentumGame::place_hero(std::string hero_race,
                                      std::string hero_class,
                                      std::string hero_name, unsigned int x,
                                      unsigned int y) {
  std::cout << "placing hero at position (" << x << ", " << y << ")"
            << std::endl;
  // std::cout << "new hero id will be " << entities_ids << std::endl;
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
      entities_cfg["critialDamageMiltiplier"].asFloat(),
      entities_cfg["inventorySize"].asInt(),
      entities_cfg["criticalDamageProbability"].asFloat(),
      entities_cfg["evasionProbability"].asFloat(),
      entities_cfg["maxSafeGoldMultiplier"].asFloat(),
      entities_cfg["levelUpLimitPower"].asFloat(),
      entities_cfg["startingXpCap"].asFloat());
  hero->add_item(new DefensiveItem(6, 7, 7));
  hero->add_item(new DefensiveItem(5, 8, 10));
  hero->equip_armour(6);
  hero->equip_helmet(5);
  hero->add_item(new DefensiveItem(6, 7, 7));
  hero->add_item(new DefensiveItem(6, 7, 7));
  hero->add_item(new DefensiveItem(2, 7, 7));
  hero->equip_shield(2);
  // hero->add_item(new Weapon(24, 25, 10, 15));
  hero->add_item(new Weapon(17, 4, 8, 5));
  hero->equip_weapon(17);
  map.ocupy_cell(x, y, entities_ids);
  heroes.emplace(entities_ids, hero);
  return entities_ids++;
}

void ArgentumGame::place_monster(unsigned int x, unsigned int y) {
  Json::Value entity = entities_cfg["npcs"]["goblin"];
  Monster *e = new Monster(entities_ids, x, y, entity["id"].asInt(), 'g',
                           entity["maxHp"].asInt(), entity["level"].asInt(),
                           entity["dps"].asInt(), std::ref(map));
  map.ocupy_cell(x, y, entities_ids);

  monsters.emplace(entities_ids++, e);
}

void ArgentumGame::print_debug_map() {
  std::unique_lock<std::mutex> lock(mutex);
  map.debug_print();
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
  // delete map;
  // Cierro cola y elimino comandos que no se podran procesar
  commands_queue->close();
  while (!commands_queue->is_empty()) {
    Command *cmd = commands_queue->pop();
    delete cmd;
  }
  // cierro y elimino las colas de notificaciones
  // for (BlockingThreadSafeQueue<Notification *> *q : queues_notifications) {
  //   q->close();
  //   Notification *n;
  //   while (!q->is_empty()) {
  //     n = q->pop();
  //     delete n;
  //   }
  //   delete q;
  // }

  std::map<unsigned int, BlockingThreadSafeQueue<Notification *> *>::iterator
      it;
  for (it = queues_notifications.begin(); it != queues_notifications.end();) {
    it->second->close();
    Notification *n;
    while (!(it->second)->is_empty()) {
      n = (it->second)->pop();
      delete n;
    }
    delete (it->second);
    it = queues_notifications.erase(it);
  }
}