#include "argentum_game.h"
//#include <jsoncpp/json/json.h>
#include "../util/json/json.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	std::ifstream file("mapa.json");
	ArgentumGame game(3, file);
	// Json::Value root;
	// file >> root;
	// std::cout << "Width: " << root["width"] << "Height: " << root["height"] << std::endl;
	// std::cout << "Layers: " << root["layers"][0]["data"][0] << std::endl;
	// config_doc >> root;
	// ArgentumGame game(3);
	// game.start();
	// usleep(60000000/7);
	// game.kill();
 //    return 0;
}
