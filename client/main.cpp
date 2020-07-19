#include <fstream>
#include <iostream>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "arguments_exceptions.h"
#include "client.h"
#include "client_arguments_validator.h"
#include "connection_exceptions.h"
#include "texture_manager.h"
#include "window_game.h"
#include "lobby.h"

TextureManager& texture_manager = TextureManager::get_instance();

int main(int argc, char* argv[]) {
  try {
    //ClientArgumentsValidator validator(argc, argv);
    //validator.validate_arguments();

    //std::ifstream config_file("../../server/cfg/entities/entities.json");
    //Json::Value config;
    //config_file >> config;
    
    WindowGame window_game;
    Lobby argentum_lobby(window_game.get_renderer());
    argentum_lobby.start_lobby();
    /*Client client(validator.get_ip(), validator.get_port(),
                  config["screenWidth"].asUInt(),
                  config["screenHeight"].asUInt());
    
    client.play();*/
    return EXIT_SUCCESS;
  } catch (ArgumentsException excep) {
    std::cout << excep.what() << std::endl;
  } catch (std::exception excep) {
    std::cout << excep.what() << std::endl;
  }
}
