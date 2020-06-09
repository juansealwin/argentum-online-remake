#include "map.h"
#include "npc_auto_mover.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib> 
//Se queda quieto un segundo.
#define REFRESH_RATE 500
int main(int argc, char *argv[]) {
    BaseCharacter *b = new BaseCharacter(4, 3);
    BaseCharacter *b2 = new BaseCharacter(12, 8);
	Map map(20,20);
	map.place_character(4, 3, b);
	map.place_character(12, 8, b2);
	map.debug_print();
	NpcAutoMover *auto_mover = new NpcAutoMover(b, map);
	NpcAutoMover *auto_mover2 = new NpcAutoMover(b2, map);

	auto_mover->start();
	auto_mover2->start();
	//map.move_character(4,3,4,4);
    std::string input;
    //while (input != "q") {
    while (true) {

		std::cout << "\x1B[2J\x1B[H";
		map.debug_print();
    	usleep(REFRESH_RATE);
    }

	delete auto_mover;
	delete auto_mover2;
    return 0;
}
