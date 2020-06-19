#include "client.h"

Client::Client(const char *host, const char *port) {
  // this->socket.connect(host, port);
}

const bool Client::valid_request(std::string &request) { return true; }

void Client::play() {
  
  Uint32 frame_start;
  int frame_time;
  BlockingQueue events_queue;
  GameRenderer game_renderer(800, 600);
  GameUpdater updater;
  EventSender sender(id_player, events_queue);
  Game game(id_player, events_queue);

  game.eventHandler();
  game_renderer.run();
  updater.run();
  sender.run();

  while (game.isRunning()) {
    /*frame_start = SDL_GetTicks();

    game.eventHandler();
    game.update();
    game.render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);*/
  }
  game_renderer.join();
  updater.join();
  sender.join();
  game.~Game();
}

void Client::send_request(const unsigned char *request, std::size_t size) {
  ClientProtocol::send_request(socket, request, size);
}

std::vector<unsigned char> Client::get_response() {
  return ClientProtocol::receive_request_response(socket);
}
