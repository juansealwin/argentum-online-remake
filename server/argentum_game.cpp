#include "argentum_game.h"

#include <iostream>

ArgentumGame::ArgentumGame(const unsigned int room_number,
                           std::ifstream &map_config)
    : room(room_number) {  //, map(20,20) {
  // Seguramente esto tenga que ser un mapa del estilo id:npc
  Json::Value map_cfg;
  map_config >> map_cfg;
  map = new Map(map_cfg);
  map_name = map_cfg["editorsettings"]["export"]["target"].asString();
  std::cout << "New game in map " << map_name << std::endl;
  place_initial_monsters(map_cfg);
}
void ArgentumGame::place_initial_monsters(Json::Value map_cfg) {
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
      character = new Monster(row, col, type, 'g');
    } else if (type == ZOMBIE) {
      character = new Monster(row, col, type, 'z');
    } else if (type == SPIDER) {
      character = new Monster(row, col, type, 'a');
    } else if (type == SKELETON) {
      character = new Monster(row, col, type, 'e');
    }
    map->place_character(row, col, character);
    // if (character) characters.push_back(character);
    if (character) characters.emplace(id, character);
    col++;
    id++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
}

void ArgentumGame::move_monsters() {
  for (auto &character : characters) {
    if (!character.second->is_movable()) {
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
      int current_x_pos = character.second->x_position;
      int current_y_pos = character.second->y_position;
      // int next_x_pos = character->x_position + 1;
      // int next_y_pos = character->y_position + 1;
      int next_x_pos = character.second->x_position + x_step;
      int next_y_pos = character.second->y_position + y_step;
      map->move_character(current_x_pos, current_y_pos, next_x_pos, next_y_pos);
    }
  }
}

void ArgentumGame::update(bool one_second_update) {
  if (one_second_update) {
    move_monsters();
  }
}

void ArgentumGame::kill() { alive = false; }

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
  const unsigned int game_updates_after = 1000;
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
      // print_debug_map();
      game_status();
      total_time_elapsed = 0;
      one_second_passed = true;
      updates = 0;
    }
  }

  // std::cout << "UPS: " << updates << std::endl;
}

void ArgentumGame::print_debug_map() {
  map->debug_print();
  std::cout << "\x1B[2J\x1B[H";
}

ArgentumGame::~ArgentumGame() {
  for (auto &character : characters) {
    delete character.second;
  }
  delete map;
  this->join();
}

unsigned int ArgentumGame::get_room() { return room; }

Json::Value ArgentumGame::game_status() {
  Json::Value status;
  status["map"] = map_name;
  status["entities"] = Json::Value(Json::arrayValue);
  for (auto &character : characters) {
    Json::Value current_entity_status;
    current_entity_status["id"] = character.first;
    current_entity_status["x_pos"] = character.second->x_position;
    current_entity_status["y_pos"] = character.second->y_position;
    current_entity_status["type"] = character.second->get_type();
    status["entities"].append(current_entity_status);
  }
  std::cout << status << std::endl << "*******************" << std::endl;
  return status;
}
