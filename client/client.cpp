#include "client.h"

#include <iostream>

#include "login_command_dto.h"

Client::Client(const char* host, const char* port) {
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

  // GameRenderer game_renderer(800, 600);
  GameUpdater updater(player_id, 800, 600, map_updated);
  ModelReceiver model_receiver(map_updated);
  CommandsSender sender(player_id, commands_to_send, socket);
  Game game(player_id, commands_to_send);

  LoginCommandDTO login_command(0);
  commands_to_send.push_event(login_command);

  game.event_handler();
  // Lanzo los hilos para renderizar, actualizar el modelo, enviar datos al
  // server
  // game_renderer.run();
  model_receiver.run();
  updater.run();
  sender.run();

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
