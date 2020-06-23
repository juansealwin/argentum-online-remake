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
  BlockingMap map_updated;

  // TODO: tambien hay que mandar el usuario
  LoginCommandDTO* login_command = new LoginCommandDTO(0);
  commands_to_send.push(login_command);

  CommandsSender sender(commands_to_send, socket);
  sender.run();

  // TODO: el server me devuelve el player_id

  // GameRenderer game_renderer(800, 600);
  GameUpdater updater(player_id, 800, 600, map_updated);
  ModelReceiver model_receiver(map_updated);
  Game game(player_id, commands_to_send);

  game.event_handler();
  // Lanzo los hilos para renderizar, actualizar el modelo, enviar datos al
  // server
  // game_renderer.run();
  model_receiver.run();
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
  model_receiver.join();
  updater.join();
  sender.join();
  game.~Game();
}
