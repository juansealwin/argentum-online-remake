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
  Game game(800, 600);
  Uint32 frame_start;
  int frame_time;

  while (game.isRunning()) {
    frame_start = SDL_GetTicks();

    game.eventHandler();
    game.update();
    game.render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);
  }
  game.~Game();
}
