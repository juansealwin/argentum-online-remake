#include "map.h"
#include "npc_auto_mover.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib> 
//Se queda quieto un segundo.
#define REFRESH_RATE 500
int main(int argc, char *argv[]) {
    BaseCharacter *b = new BaseCharacter(4, 3);
    BaseCharacter *b2 = new BaseCharacter(6, 15);
    BaseCharacter *b3 = new BaseCharacter(7, 15);
    BaseCharacter *b4 = new BaseCharacter(8, 15);
    BaseCharacter *b5 = new BaseCharacter(9, 15);
    BaseCharacter *b6 = new BaseCharacter(10, 15);
    BaseCharacter *b7 = new BaseCharacter(11, 15);
    BaseCharacter *b8 = new BaseCharacter(12, 15);


	Map map(20,20);
	map.place_character(4, 3, b);
	map.place_character(6, 15, b2);
	map.place_character(7, 15, b3);
	map.place_character(8, 15, b4);
	map.place_character(9, 15, b5);
	map.place_character(10, 15, b6);
	map.place_character(11, 15, b7);
	map.place_character(12, 15, b8);

	map.debug_print();
	NpcAutoMover *auto_mover = new NpcAutoMover(b, map);
	NpcAutoMover *auto_mover2 = new NpcAutoMover(b2, map);
	NpcAutoMover *auto_mover3 = new NpcAutoMover(b3, map);
	NpcAutoMover *auto_mover4 = new NpcAutoMover(b4, map);
	NpcAutoMover *auto_mover5 = new NpcAutoMover(b5, map);
	NpcAutoMover *auto_mover6 = new NpcAutoMover(b6, map);
	NpcAutoMover *auto_mover7 = new NpcAutoMover(b7, map);
	NpcAutoMover *auto_mover8 = new NpcAutoMover(b8, map);


	auto_mover->start();
	auto_mover2->start();
	auto_mover3->start();
	auto_mover4->start();
	auto_mover5->start();
	auto_mover6->start();
	auto_mover7->start();
	auto_mover8->start();

	//map.move_character(4,3,4,4);
    unsigned long long twominsimulation = 0;
    //while (input != "q") {
    while (true) {

		std::cout << "\x1B[2J\x1B[H";
		map.debug_print();
		twominsimulation += REFRESH_RATE;
		if (twominsimulation >= 40000000) {
			break;
    	}
    	usleep(REFRESH_RATE);

    }

	delete auto_mover;
	delete auto_mover2;
	delete auto_mover3;
	delete auto_mover4;
	delete auto_mover5;
	delete auto_mover6;
	delete auto_mover7;
	delete auto_mover8;
    return 0;
}
