#include "client.h"
#include <iostream>

Client::Client(const char* host, const char* port) {
  Socket socket;
  socket.connect(host, port);
  this->socket = std::move(socket);
}

Client::~Client() {}

const bool Client::valid_request(std::string& request) { return true; }

void Client::play() {
  Json::Value starting_info;
  starting_info["room_number"] = 1;
  Json::FastWriter fastWriter;
  std::string starting_info_string = fastWriter.write(starting_info);
  std::cout << "lo que envio: " << starting_info_string << std::endl;
  Protocol::sendMessage(socket, starting_info_string);
  std::cout << "lo mandé\n";


  // Game game(800, 600);
  // Uint32 frame_start;
  // int frame_time;

  // while (game.isRunning()) {
  //   frame_start = SDL_GetTicks();

  //   game.eventHandler();
  //   game.update();
  //   game.render();

  //   frame_time = SDL_GetTicks() - frame_start;

  //   if (FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);
  // }
  // game.~Game();
}

// void Client::send_request(const unsigned char* request, std::size_t size) {
//   ClientProtocol::send_request(socket, request, size);
// }

// std::vector<unsigned char> Client::get_response() {
//   return ClientProtocol::receive_request_response(socket);
// }
