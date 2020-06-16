#include "argentum_game.h"

#include <iostream>

ArgentumGame::ArgentumGame(const unsigned int room_number,
                           ThreadSafeQueue<Command *> *commands_queue,
                           std::ifstream &map_config,
                           std::ifstream &entities_config)
    : room(room_number),
      commands_queue(commands_queue),
      mutex() {  //, map(20,20) {
  // Seguramente esto tenga que ser un mapa del estilo id:npc
  std::unique_lock<std::mutex> lock(mutex);
  Json::Value map_cfg;
  map_config >> map_cfg;
  entities_config >> entities_cfg;
  map = new Map(map_cfg);
  map_name = map_cfg["editorsettings"]["export"]["target"].asString();
  std::cout << "New game in map " << map_name << std::endl;
  std::cout << "Entities cfg: " << std::endl << entities_cfg;
  place_initial_monsters(map_cfg);
}
void ArgentumGame::place_initial_monsters(Json::Value map_cfg) {
  // std::unique_lock<std::mutex> lock(mutex);
  int row = 0;
  int col = 0;
  int map_cols = map_cfg["width"].asInt();
  unsigned int id = 0;
  for (const auto &jv : map_cfg["layers"][2]["data"]) {
    BaseCharacter *character = nullptr;
    int type = jv.asInt();
    // en el futuro podria simplificarse, el caracter lo recibo para debug

    if (type == PRIEST) {
      character = new BaseCharacter(row, col, type, 'p');
    } else if (type == MERCHANT) {
      character = new BaseCharacter(row, col, type, 'm');
    } else if (type == BANKER) {
      character = new BaseCharacter(row, col, type, 'b');
    } else if (type == GOBLIN) {
      Json::Value entity = entities_cfg["npcs"]["goblin"];
      character = new Monster(row, col, type, 'g', entity["maxHp"].asInt(),
                              entity["level"].asInt(), entity["dps"].asInt());
    } else if (type == ZOMBIE) {
      Json::Value entity = entities_cfg["npcs"]["zombie"];

      character = new Monster(row, col, type, 'g', entity["maxHp"].asInt(),
                              entity["level"].asInt(), entity["dps"].asInt());
    } else if (type == SPIDER) {
      Json::Value entity = entities_cfg["npcs"]["spider"];

      character = new Monster(row, col, type, 'g', entity["maxHp"].asInt(),
                              entity["level"].asInt(), entity["dps"].asInt());
    } else if (type == SKELETON) {
      Json::Value entity = entities_cfg["npcs"]["skeleton"];

      character = new Monster(row, col, type, 'g', entity["maxHp"].asInt(),
                              entity["level"].asInt(), entity["dps"].asInt());
    }
    map->place_character(row, col, character);
    // if (character) characters.push_back(character);
    if (character) {
      entities.emplace(id, character);
      id++;
    }
    col++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
}

void ArgentumGame::move_entity(int entity_id, int x, int y) {
  Entity *entity = entities.at(entity_id);
  map->move_character(entity->x_position, entity->y_position, x, y);
}

void ArgentumGame::auto_move_monsters() {
  for (auto &entity : entities) {
    if (!entity.second->is_movable()) {
      continue;
    } else {
      int x_step = rand() % 2;  // Si es 0, se queda quieto. Si es 1, se mueve.
      int y_step = rand() % 2;
      int y_top = rand() % 2;
      if (y_top == 1) {
        y_step *= -1;
      }
      int x_left = rand() % 2;
      if (x_left == 1) {
        x_step *= -1;
      }
      int current_x_pos = entity.second->x_position;
      int current_y_pos = entity.second->y_position;
      // int next_x_pos = entity->x_position + 1;
      // int next_y_pos = entity->y_position + 1;
      int next_x_pos = entity.second->x_position + x_step;
      int next_y_pos = entity.second->y_position + y_step;
      map->move_character(current_x_pos, current_y_pos, next_x_pos, next_y_pos);
    }
  }
}

void ArgentumGame::update(bool one_second_update) {
  std::unique_lock<std::mutex> lock(mutex);
  if (one_second_update) {
    auto_move_monsters();
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
