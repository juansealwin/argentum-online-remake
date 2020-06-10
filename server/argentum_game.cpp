#include "argentum_game.h"
#include <iostream>

ArgentumGame::ArgentumGame
	(const unsigned int room_number) : room(room_number), map(20,20) {
	//Seguramente esto tenga que ser un mapa del estilo id:npc
	characters.reserve(8);
    for (int x = 1; x < 9; ++x ) {
          BaseCharacter *character = new BaseCharacter(x, 3);
          map.place_character(x, 3, character);
          characters.push_back(character); 
    }
}

void ArgentumGame::move_monsters() {
  for (auto &monster : characters)
  {
	int x_step = rand() % 2; //Si es 0, se queda quieto. Si es 1, se mueve.
    int y_step = rand() % 2;
    int y_top = rand() % 2;
    if (y_top == 1) {
      	y_step*= -1;
    }
    int x_left = rand() % 2;
    if (x_left == 1) {
      	x_step *= -1;
    }
    int current_x_pos = monster->x_position;
    int current_y_pos = monster->y_position;
    int next_x_pos = monster->x_position + x_step;
    int next_y_pos = monster->y_position + y_step;
    map.move_character(current_x_pos, current_y_pos, next_x_pos, next_y_pos);
  }
}

void ArgentumGame::update() {
	move_monsters();
}

void ArgentumGame::run() {
    while (alive) {
       update();
       map.debug_print();
	   usleep(25);
    }
}

ArgentumGame::~ArgentumGame() {
	alive = false;
	this->join();
}

const unsigned int ArgentumGame::get_room() {
	return room;
}
