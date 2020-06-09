#include "map.h"
#include "npc_auto_mover.h"
#include <iostream>
int main(int argc, char *argv[]) {
    BaseCharacter *b = new BaseCharacter(4, 3);
	Map map(20,20, b);
	map.debug_print();
	NpcAutoMover *auto_mover = new NpcAutoMover(b, map);
	auto_mover->start();
	//map.move_character(4,3,4,4);
    std::string input;
    while (input != "q") {
		std::cout << "\x1B[2J\x1B[H";
		map.debug_print();
		std::cin >> input;
    }

	delete auto_mover;
    return 0;
}
