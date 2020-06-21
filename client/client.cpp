#include "client.h"
#include <iostream>

Client::Client(const char* host, const char* port) {
  Socket socket;
  socket.connect(host, port);
  this->socket = std::move(socket);

  Json::Value starting_info;
  starting_info["roomNumber"] = 0;
  Protocol::sendMessage(this->socket, starting_info);
}

Client::~Client() {}

const bool Client::valid_request(std::string& request) { return true; }

void Client::play() {
  
  //Uint32 frame_start;
  //int frame_time;

  BlockingQueue events_to_send;
  BlockingMap map_updated;
  
  //GameRenderer game_renderer(800, 600);
  GameUpdater updater(id_player, 800, 600, map_updated);
  ModelReceiver model_receiver(map_updated);
  EventSender sender(id_player, events_to_send);
  Game game(id_player, events_to_send);

  game.event_handler();
  // Lanzo los hilos para renderizar, actualizar el modelo, enviar datos al server
  //game_renderer.run();
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
  //game_renderer.join();
  model_receiver.join();
  updater.join();
  sender.join();
  game.~Game();
}
