#include "argentum_game.h"
#include <iostream>

ArgentumGame::ArgentumGame
	(const unsigned int room_number, std::ifstream &map_config) : 
  room(room_number) { //, map(20,20) {
	//Seguramente esto tenga que ser un mapa del estilo id:npc
  Json::Value root;
  map_config >> root;
  //std::cout << "Width: " << root["width"] << "Height: " << root["height"] << std::endl;
  map = new Map(root);
  place_initial_monsters(root);
  //map->debug_print();
	// characters.reserve(8);
 //    for (int x = 1; x < 9; ++x ) {
 //          BaseCharacter *character = new BaseCharacter(x, 3);
 //          map.place_character(x, 3, character);
 //          characters.push_back(character); 
 //    }
}
void ArgentumGame::place_initial_monsters(Json::Value root){

  int row = 0;
  int col = 0;
  int map_cols = root["width"].asInt();
  for (const auto& jv: root["layers"][1]["data"])
  {
    BaseCharacter *character = nullptr;
    int type = jv.asInt();
    // en el futuro podria simplificarse, el caracter lo recibo para debug
    if (type == PRIEST) {
      character = new BaseCharacter(row, col, type ,'p');
      map->place_character(row, col, character );
    } else if (type == MERCHANT) {
      character = new BaseCharacter(row, col, type ,'m');
      map->place_character(row, col, character );
    } else if (type == BANKER) {
      character = new BaseCharacter(row, col, type ,'b');
      map->place_character(row, col, character );
    } else if (type == GOBLIN) {
      character = new Monster(row, col, type ,'g');
      map->place_character(row, col, character );
    } else if (type == ZOMBIE) {
      character = new Monster(row, col, type ,'z');
      map->place_character(row, col, character );
    } else if (type == SPIDER) {
      character = new Monster(row, col, type ,'a');
      map->place_character(row, col, character );
    } else if (type == SKELETON) {
      character = new Monster(row, col, type ,'e');
      map->place_character(row, col, character );
    }
    if (character) characters.push_back(character);
    col++;
    if (col == map_cols) {
      row++;
      col = 0;
    }
  }
}

void ArgentumGame::move_monsters() {
  for (auto &character : characters)
  {
    if (!character->is_movable()) {
       continue;
    }
    else {
  	  //int x_step = rand() % 2; //Si es 0, se queda quieto. Si es 1, se mueve.
      //int y_step = rand() % 2;
      //int y_top = rand() % 2;
      //if (y_top == 1) {
      //  	y_step*= -1;
      //}
      //int x_left = rand() % 2;
      //if (x_left == 1) {
      //  	x_step *= -1;
     // }
      int current_x_pos = character->x_position;
      int current_y_pos = character->y_position;
      int next_x_pos = character->x_position + 1;
      int next_y_pos = character->y_position + 1;

      //int next_x_pos = character->x_position + x_step;
      //int next_y_pos = character->y_position + y_step;
      map->move_character(current_x_pos, current_y_pos, next_x_pos, next_y_pos);
    }
  }
}

void ArgentumGame::update(unsigned long long seconds) {
  if (seconds % 1000000 == 0) {
	  move_monsters();
  }
}

void ArgentumGame::kill() {
  alive = false;
}

void ArgentumGame::run() {
  //tiempo que transcurrio en MICROSEGUNDOS
    unsigned long long time_elapsed = 0;
    int last_duration = 0;
    while (alive) {
       auto t1 = std::chrono::high_resolution_clock::now();
       update(time_elapsed);
       auto t2 = std::chrono::high_resolution_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
       //aca deberia dormir 60 - el tiempo que me lleve update
       if (duration > last_duration) {
         last_duration = duration;
       }
       //usleep(60 - duration);
       //time_elapsed += 60 - duration;

    }
    std::cout << "Cantidad de monstruos: " << characters.size() << std::endl;
    std::cout << "Maxima duracion del loop: " << last_duration << std::endl;
}

void ArgentumGame::print_debug_map() {
  map->debug_print();
  std::cout << "\x1B[2J\x1B[H";
}

ArgentumGame::~ArgentumGame() {

	for (auto &monster : characters)
	{
		delete monster;
	}
  delete map;
	this->join();
}

const unsigned int ArgentumGame::get_room() {
	return room;
}
