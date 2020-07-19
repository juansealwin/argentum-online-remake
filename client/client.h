#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "commands_blocking_queue.h"
#include "commands_sender.h"
#include "common_socket.h"
#include "event_handler.h"
#include "events_queue.h"
#include "game.h"
#include "game_renderer.h"
#include "game_updater.h"
#include "helper_functions.h"
#include "login_command_dto.h"
#include "protocol.h"
#include "texture.h"

class Client {
 private:
  int player_id;
  Socket socket;
  bool is_running;
  int screen_width;
  int screen_height;

 public:
  Client(const char* host, const char* port, const int screen_width,
         const int screen_height);
  ~Client();
  void play();
};

#endif
