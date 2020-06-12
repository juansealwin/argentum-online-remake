#include "argentum_game.h"
//#include <jsoncpp/json/json.h>
#include "../util/json/json.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	std::ifstream file("mapa.json");
	ArgentumGame game(3, file);
	game.start();
	unsigned long long x = 20000000;
	unsigned long long x2 = 0;
	//while (x2 < x) {
		//game.print_debug_map();
	//	usleep(1000000);

	//	x2 += 1000000;

	//}
	usleep(10000);
	game.kill();

    return 0;
}
