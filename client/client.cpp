#include "client.h"

Client::Client(const char *host, const char *port) {
  // this->socket.connect(host, port);
}

const bool Client::valid_request(std::string &request) { return true; }

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

void Client::send_request(const unsigned char *request, std::size_t size) {
  ClientProtocol::send_request(socket, request, size);
}

std::vector<unsigned char> Client::get_response() {
  return ClientProtocol::receive_request_response(socket);
}