#include "argentum_game.h"

#include <iostream>

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
  std::cout << "New game in map " << map_name << std::endl;
  place_initial_npcs(map_cfg);
  place_initial_monsters(map_cfg);
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
      e = new Priest(row, col, type, 'p');
    } else if (type == MERCHANT) {
      e = new Merchant(row, col, type, 'm');
    } else if (type == BANKER) {
      e = new Banker(row, col, type, 'b');
    }
    if (e) {
      // map->place_entity(row, col, e);
      map->ocupy_cell(row, col);
      entities.emplace(entities_ids, e);
      entities_ids++;
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
    Entity *e = nullptr;
    int type = jv.asInt();
    // en el futuro podria simplificarse, el caracter lo recibo para debug
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
      e = new Monster(row, col, entity["id"].asInt(), 'g',
                      entity["maxHp"].asInt(), entity["level"].asInt(),
                      entity["dps"].asInt(), map);
    }
    if (e) {
      // map->place_entity(row, col, e);
      map->ocupy_cell(row, col);
      entities.emplace(entities_ids, e);
      entities_ids++;
    }
    col++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
  // Entity *e = new Monster(99, 99, 133, 'g', 133, 133, 133, map);
  // map->ocupy_cell(0, 99);
  // entities.emplace(entities_ids, e);
  // entities_ids++;
  add_new_hero("human", "warrior");
}

void ArgentumGame::move_entity(int entity_id, int x, int y) {
  Entity *entity = entities.at(entity_id);
  map->ocupy_cell(x, y);
  map->empty_cell(entity->x_position, entity->y_position);
}

void ArgentumGame::add_new_hero(std::string hero_race, std::string hero_class) {
  Json::Value race_stats = entities_cfg["races"][hero_race];
  Json::Value class_stats = entities_cfg["classes"][hero_class];
  std::tuple<int, int> free_tile = map->get_random_free_space();
  int x = std::get<0>(free_tile);
  int y = std::get<1>(free_tile);
  Hero *hero = new Hero(
      x, y, race_stats["id"].asInt(), 'h', class_stats["level"].asInt(),
      race_stats["strength"].asInt() + class_stats["strength"].asInt(),
      race_stats["intelligence"].asInt() + class_stats["intelligence"].asInt(),
      race_stats["agility"].asInt() + class_stats["agility"].asInt(),
      race_stats["constitution"].asInt(), class_stats["fClassHp"].asInt(),
      race_stats["fRaceHp"].asInt(), race_stats["fRaceRecovery"].asInt(),
      race_stats["fRaceMana"].asInt(), class_stats["fClassMana"].asInt(),
      class_stats["fClassMeditation"].asInt(), race_stats["gold"].asInt(),
      class_stats["id"].asInt(), map);
  map->ocupy_cell(x, y);
  entities.emplace(entities_ids, hero);
  entities_ids++;
}

void ArgentumGame::update(bool one_second_update) {
  std::unique_lock<std::mutex> lock(mutex);
  if (one_second_update) {
    // auto_move_monsters();
    for (auto &entity : entities) {
      entity.second->update();
    }
  }
  while (!commands_queue->is_empty()) {
    Command *cmd = commands_queue->pop();
    cmd->execute(this);
    delete cmd;
  }
}

void ArgentumGame::kill() {
  std::unique_lock<std::mutex> lock(mutex);
  alive = false;
}

static unsigned long long MSTimeStamp() {
  typedef std::chrono::steady_clock sc;
  unsigned long long ms_since_epoch =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          sc::now().time_since_epoch())
          .count();
  return ms_since_epoch;
}

void ArgentumGame::run() {
  unsigned long long t1 = MSTimeStamp();
  unsigned long long t2 = 0;
  unsigned long long delta = 0;
  unsigned long long time_elapsed = 0;
  unsigned long long delay = 0;
  unsigned long long total_time_elapsed = 0;
  bool one_second_passed = false;
  const unsigned int game_updates_after = 850;  // A TUNEAR
  int updates = 0;
  // con este valor obtengo acerca de 60 updates por segundo, con la idea de
  // que el juego corra a 60fps.
  const unsigned int ups = 17;
  while (alive) {
    update(one_second_passed);
    one_second_passed &= false;
    updates++;
    t2 = MSTimeStamp();  // 0
    time_elapsed += t2 - t1 + delta;
    total_time_elapsed += t2 - t1 + delta;
    delay = ups - time_elapsed;
    if (time_elapsed < ups) {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      delta = MSTimeStamp() - t2 - delay;
    } else {
      delta = 0;
    }
    t1 = MSTimeStamp();
    if (total_time_elapsed >= game_updates_after) {
      print_debug_map();
      total_time_elapsed = 0;
      one_second_passed = true;
      updates = 0;
      // game_status();
      // commands_queue->push(new MoveCommand(14, 0, 0));
      // MoveCommand cmd(14, 0, 0);
      // cmd.execute(this);
    }
  }

  // std::cout << "UPS: " << updates << std::endl;
}

void ArgentumGame::print_debug_map() {
  std::unique_lock<std::mutex> lock(mutex);
  map->debug_print();
  std::cout << "\x1B[2J\x1B[H";
}

ArgentumGame::~ArgentumGame() {
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
  this->join();
}

unsigned int ArgentumGame::get_room() { return room; }

Json::Value ArgentumGame::game_status() {
  std::unique_lock<std::mutex> lock(mutex);
  Json::Value status;
  status["map"] = map_name;
  status["op"] = "game_status";
  status["entities"] = Json::Value(Json::arrayValue);
  for (auto &entity : entities) {
    Json::Value current_entity_status;
    current_entity_status["id"] = entity.first;
    current_entity_status["x"] = entity.second->x_position;
    current_entity_status["y"] = entity.second->y_position;
    current_entity_status["type"] = entity.second->get_type();
    status["entities"].append(current_entity_status);
    // std::cout << status << std::endl;
    // std::cout << "id: " << entity.first << " at: "
    //           << "(" << entity.second->x_position << ", "
    //           << entity.second->y_position << ")" << std::endl;
  }
  return status;
}
