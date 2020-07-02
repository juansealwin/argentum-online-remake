#include "argentum_game.h"

#include <iostream>

#include "defensive_item.h"
#include "weapon.h"
ArgentumGame::ArgentumGame(const unsigned int room_number,
                           ThreadSafeQueue<Command *> *commands_queue,
                           std::ifstream &map_config,
                           std::ifstream &entities_config)
    : room(room_number), commands_queue(commands_queue), mutex() {
  std::unique_lock<std::mutex> lock(mutex);
  Json::Value map_cfg;
  map_config >> map_cfg;
  entities_config >> entities_cfg;
  map = new Map(map_cfg);
  map_name = map_cfg["editorsettings"]["export"]["target"].asString();
  std::cout << "New game in " << map_name << std::endl;
  place_initial_npcs(map_cfg);
  place_initial_monsters(map_cfg);

  tests_proyectiles();
}

void ArgentumGame::tests_proyectiles() {
  std::cout << "Running tests" << std::endl;
  place_hero("human", "warrior", "test_name1", 10, 23);
  throw_projectile(15);
  place_hero("human", "warrior", "test_name1", 0, 0);
  place_hero("human", "warrior", "test_name1", 1, 0);
  place_monster(2, 0);
  throw_projectile(17);
  throw_projectile(18);
  place_hero("human", "warrior", "test_name1", 0, 3);
  place_hero("human", "warrior", "test_name1", 5, 3);
  throw_projectile(22);
  throw_projectile(23);
  place_monster(10, 3);
  unsigned int hero1 = place_hero("human", "warrior", "test_name1", 99, 0);
  unsigned int hero2 = place_hero("human", "warrior", "test_name1", 98, 1);
  throw_projectile(hero1);
  throw_projectile(hero2);
  unsigned int hero3 = place_hero("human", "warrior", "test_name1", 5, 16);
  unsigned int hero4 = place_hero("human", "warrior", "test_name1", 5, 16);
  throw_projectile(hero3);
  throw_projectile(hero4);
}

void ArgentumGame::place_initial_npcs(Json::Value map_cfg) {
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
      // map->place_entity(row, col, e);
      map->ocupy_cell(row, col, entities_ids);
      entities.emplace(entities_ids++, e);
    }
    col++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
}

void ArgentumGame::place_initial_monsters(Json::Value map_cfg) {
  // std::unique_lock<std::mutex> lock(mutex);
  int row = 0;
  int col = 0;
  int map_cols = map_cfg["width"].asInt();
  for (const auto &jv : map_cfg["layers"][2]["data"]) {
    Monster *e = nullptr;
    int type = jv.asInt();
    Json::Value entity = Json::arrayValue;
    if (type == GOBLIN) {
      entity = entities_cfg["npcs"]["goblin"];
    } else if (type == ZOMBIE) {
      entity = entities_cfg["npcs"]["zombie"];
    } else if (type == SPIDER) {
      entity = entities_cfg["npcs"]["spider"];
    } else if (type == SKELETON) {
      entity = entities_cfg["npcs"]["skeleton"];
    }
    if (type == GOBLIN || type == ZOMBIE || type == SPIDER ||
        type == SKELETON) {
      e = new Monster(entities_ids, row, col, entity["id"].asInt(), 'g',
                      entity["maxHp"].asInt(), entity["level"].asInt(),
                      entity["dps"].asInt(), map);
    }
    if (e) {
      // map->place_entity(row, col, e);
      map->ocupy_cell(row, col, entities_ids);
      monsters.emplace(entities_ids, e);
      entities.emplace(entities_ids++, e);
      // entities_ids++;
    }
    col++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
}

/*********************** Acciones personajes *************************/
void ArgentumGame::move_entity(int entity_id, int x, int y) {
  BaseCharacter *character =
      dynamic_cast<BaseCharacter *>(entities.at(entity_id));
  character->move(character->x_position + x, character->y_position + y);
}

void ArgentumGame::throw_projectile(int attacker_id) {
  std::cout << "throwing projectile " << std::endl;
  Hero *hero = dynamic_cast<Hero *>(entities.at(attacker_id));
  if (hero) {
    // manejar errores despues
    // errores del heroe, y de posicion contigua inaccesible
    std::tuple<unsigned int, bool, unsigned int, unsigned int> attack =
        hero->attack();
    unsigned int dmg = std::get<0>(attack);
    bool critical = std::get<1>(attack);
    unsigned int item_id = std::get<2>(attack);
    unsigned int range = std::get<3>(attack);
    std::tuple<unsigned int, unsigned int> projectile_position =
        get_contiguous_position(hero);
    unsigned int x = std::get<0>(projectile_position);
    unsigned int y = std::get<1>(projectile_position);
    Projectile *projectile =
        new Projectile(entities_ids, x, y, item_id, 'p', dmg, critical,
                       attacker_id, range, hero->orientation, map);
    projectiles.emplace(entities_ids, projectile);
    entities.emplace(entities_ids++, projectile);
  } else {
    std::cout
        << "@@@@@@@@@@@@attemp to throw proyectile not being hero@@@@@@@@@"
        << std::endl;
    std::cout << "attacker id: " << attacker_id << std::endl;
  }
}

/*********************** Fin acciones personajes *********************/

unsigned int ArgentumGame::add_new_hero(std::string hero_race,
                                        std::string hero_class,
                                        std::string hero_name) {
  std::tuple<int, int> free_tile = map->get_random_free_space();
  int x = std::get<0>(free_tile);
  int y = std::get<1>(free_tile);
  return place_hero(hero_race, hero_class, hero_name, x, y);
}

void ArgentumGame::update() {
  std::unique_lock<std::mutex> lock(mutex);
  // pensar bien que hacer primero, ejecutar los comandos o updatear el mundo?
  while (!commands_queue->is_empty()) {
    Command *cmd = commands_queue->pop();
    cmd->execute(this);
    delete cmd;
  }

  heroes_manager.update(std::ref(heroes));
  monsters_manager.update(std::ref(monsters));
  projectile_manager.update(std::ref(heroes), std::ref(monsters),
                            std::ref(projectiles));

  remove_death_entities();
  // TO DO:
  // - Chequear si monstruos murieron para eliminarlos del mapa y poner sus
  // drops
  // Desconexion de clientes: Podria ser un command a ejecutar
}

void ArgentumGame::kill() {
  std::unique_lock<std::mutex> lock(mutex);
  alive = false;
}

void ArgentumGame::run() {
  auto start = std::chrono::high_resolution_clock::now();
  // bool one_second_passed;

  while (alive) {
    // one_second_passed = false;
    auto initial = std::chrono::high_resolution_clock::now();
    // auto time_difference = initial - start;
    // if (time_difference.count() >= 1000000000) {
    //   one_second_passed = true;
    //   start = initial;
    // }
    // update(one_second_passed);
    update();
    send_game_status();
    // print_debug_map();
    long time_step = 1000 / 60.f;  // 60fps
    auto final = std::chrono::high_resolution_clock::now();
    auto loop_duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
    long sleep_time = time_step - loop_duration.count();
    if (sleep_time > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
  }
}

void ArgentumGame::print_debug_map() {
  std::unique_lock<std::mutex> lock(mutex);
  map->debug_print();
  std::cout << "\x1B[2J\x1B[H";
}

ArgentumGame::~ArgentumGame() {
  std::unique_lock<std::mutex> lock(mutex);
  for (auto &entity : entities) {
    delete entity.second;
  }
  delete map;
  // Cierro cola y elimino comandos que no se podran procesar
  commands_queue->close();
  while (!commands_queue->is_empty()) {
    Command *cmd = commands_queue->pop();
    delete cmd;
  }
  // cierro y elimino las colas de notificaciones
  for (BlockingThreadSafeQueue<Notification *> *q : queues_notifications) {
    q->close();
    Notification *n;
    while (!q->is_empty()) {
      n = q->pop();
      delete n;
    }
    delete q;
  }
}

unsigned int ArgentumGame::get_room() { return room; }

std::vector<unsigned char> ArgentumGame::send_game_status() {
  std::unique_lock<std::mutex> lock(mutex);
  std::vector<unsigned char> game_status =
      Serializer::serialize_game_status(this);
  for (BlockingThreadSafeQueue<Notification *> *q : queues_notifications) {
    q->push(new GameStatusNotification(game_status));
  }

  return game_status;
}

void ArgentumGame::add_notification_queue(
    BlockingThreadSafeQueue<Notification *> *queue) {
  std::unique_lock<std::mutex> lock(mutex);
  queues_notifications.push_back(queue);
}

void ArgentumGame::clean_notifications_queues() {
  std::unique_lock<std::mutex> lock(mutex);
  std::vector<BlockingThreadSafeQueue<Notification *> *>::iterator it;
  for (it = queues_notifications.begin(); it != queues_notifications.end();) {
    if ((*it)->is_closed()) {
      Notification *n;
      while (!(*it)->is_empty()) {
        n = (*it)->pop();
        delete n;
      }
      delete (*it);
      it = queues_notifications.erase(it);
    } else
      ++it;
  }
}

/* private methods */

void ArgentumGame::remove_death_entities() {
  for (auto it = monsters.cbegin(); it != monsters.cend();) {
    if (it->second->alive == false) {
      it = monsters.erase(it++);
    } else {
      ++it;
    }
  }
  for (auto it = entities.cbegin(); it != entities.cend();) {
    if (it->second->alive == false) {
      // aca antes de borrar al bicho llamar a algun metodo polimorfico que
      // devuelva un drop (o no) para poner en el mapa
      int x_pos = it->second->x_position;
      int y_pos = it->second->y_position;
      map->empty_cell(x_pos, y_pos);
      delete it->second;
      it = entities.erase(it++);
    } else {
      ++it;
    }
  }
}

std::tuple<unsigned int, unsigned int> ArgentumGame::get_contiguous_position(
    BaseCharacter *character) {
  unsigned int x_pos = character->x_position;
  unsigned int y_pos = character->y_position;
  switch (character->orientation) {
    case (orientation_left):
      y_pos--;
      break;
    case (orientation_right):
      y_pos++;
      break;
    case (orientation_down):
      x_pos++;
      break;
    case (orientation_up):
      x_pos--;
      break;
  }
  return std::tuple<unsigned int, unsigned int>(x_pos, y_pos);
}
unsigned int ArgentumGame::place_hero(std::string hero_race,
                                      std::string hero_class,
                                      std::string hero_name, unsigned int x,
                                      unsigned int y) {
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
      class_stats["id"].asUInt(), map, hero_name);
  hero->add_item(new DefensiveItem(6, 7, 7));
  hero->add_item(new DefensiveItem(2, 8, 10));
  hero->equip_armour(6);
  hero->equip_helmet(2);
  hero->add_item(new DefensiveItem(6, 7, 7));
  hero->add_item(new DefensiveItem(6, 7, 7));
  hero->add_item(new DefensiveItem(90, 7, 7));
  hero->equip_shield(90);
  hero->add_item(new Weapon(24, 25, 10, 15));
  hero->equip_weapon(24);
  std::cout << "---------placing hero with id-----------: " << entities_ids
            << std::endl;
  map->ocupy_cell(x, y, entities_ids);
  entities.emplace(entities_ids, hero);
  heroes.emplace(entities_ids, hero);
  return entities_ids++;
}

void ArgentumGame::place_monster(unsigned int x, unsigned int y) {
  Json::Value entity = entities_cfg["npcs"]["goblin"];
  Monster *e = new Monster(entities_ids, x, y, entity["id"].asInt(), 'g',
                           entity["maxHp"].asInt(), entity["level"].asInt(),
                           entity["dps"].asInt(), map);
  map->ocupy_cell(x, y, entities_ids);
  monsters.emplace(entities_ids, e);
  std::cout << "Placing monster with id" << entities_ids << std::endl;
  entities.emplace(entities_ids++, e);
}