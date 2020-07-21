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
#include "connection_exceptions.h"
#include "event_handler.h"
#include "events_queue.h"
#include "game.h"
#include "game_renderer.h"
#include "game_updater.h"
#include "login_command_dto.h"
#include "protocol.h"
#include "texture.h"
#include "window_game.h"

class Client {
 private:
  int player_id;
  int initial_map;
  Socket socket;
  bool is_running;
  WindowGame& window_game;

 public:
  Client(const char*, const char*, WindowGame&);
  ~Client();
  void play();
  void do_handshake(std::string, std::string, std::string, int);
};

#endif
