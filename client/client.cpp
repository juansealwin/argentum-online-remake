#include "client.h"

#include <iostream>

#include "login_command_dto.h"

Client::Client(const char* host, const char* port) : player_id(0) {
  Socket socket;
  socket.connect(host, port);
  this->socket = std::move(socket);
}

Client::~Client() {}

void Client::play() {
  // Uint32 frame_start;
  // int frame_time;
  CommandsBlockingQueue commands_to_send;

  // TODO: tambien hay que mandar el usuario
  LoginCommandDTO* login_command = new LoginCommandDTO(0);
  commands_to_send.push(login_command);

  CommandsSender sender(commands_to_send, socket);
  sender.run();
  ProtectedMap protected_map;
  // TODO: el server me devuelve el player_id

  // GameRenderer game_renderer(800, 600);
  GameUpdater updater(protected_map, socket);
  Game game(player_id, commands_to_send);

  // Lanzo los hilos para renderizar, actualizar el modelo, enviar datos al
  // server
  // game_renderer.run();
  updater.run();

  while (game.is_up()) {
    /*frame_start = SDL_GetTicks();

    game.eventHandler();
    game.update();
    game.render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);*/
  }
  // game_renderer.join();
  updater.join();
  sender.join();
  game.~Game();
}
