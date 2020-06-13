#include "argentum_game.h"
//#include <jsoncpp/json/json.h>
#include "../util/json/json.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	std::ifstream file("mapa.json");
	ArgentumGame game(3, file);
	//game.print_debug_map();

	game.start();

	usleep(1000000);
	//game.print_debug_map();

	game.kill();

    return 0;
}
