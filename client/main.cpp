#include <fstream>
#include <iostream>

#include "arguments_exceptions.h"
#include "client.h"
#include "client_arguments_validator.h"
#include "connection_exceptions.h"
#include "lobby.h"
#include "texture_manager.h"
#include "window_game.h"

TextureManager& texture_manager = TextureManager::get_instance();

int main(int argc, char* argv[]) {
  try {
    ClientArgumentsValidator validator(argc, argv);
    validator.validate_arguments();
    WindowGame window_game;
    Lobby argentum_lobby(window_game.get_window(), window_game.get_renderer());

    // Chequeamos si el lobby se ejecuto con exito o si se cerro
    if (argentum_lobby.start_lobby()) {
      Client client(validator.get_ip(), validator.get_port(), window_game);

      // Redimensionamos la pantalla dependiendo de las preferencias del usuario
      window_game.resize_screen(argentum_lobby.get_screen_width(),
                                argentum_lobby.get_screen_height(),
                                argentum_lobby.get_fs_mode());

      // Seteamos la relación de ancho y alto de resolución
      texture_manager.set_aspect_ratio(window_game.get_width_ratio(),
                                       window_game.get_height_ratio());

      // Hacemos el handshake con el server
      client.do_handshake(
          argentum_lobby.get_user_name(), argentum_lobby.get_player_race(),
          argentum_lobby.get_player_class(), argentum_lobby.get_initial_map());

      // Comenzamos el juego
      client.play();
    }
    return EXIT_SUCCESS;
  } catch (ArgumentsException& excep) {
    std::cout << excep.what() << std::endl;
  } catch (ConnectionException& excep) {
    std::cout << excep.what() << std::endl;
  } catch (std::exception& excep) {
    std::cout << excep.what() << std::endl;
  }
}
