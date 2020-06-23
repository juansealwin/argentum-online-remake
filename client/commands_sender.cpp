#include "commands_sender.h"

CommandsSender::CommandsSender(const int player_id,
                               CommandsBlockingQueue& commands_queue,
                               const Socket& socket)
    : player_id(player_id), commands_queue(commands_queue), socket(socket) {}

CommandsSender::~CommandsSender() {}

void CommandsSender::run() {
  try {
    while (is_running) {
      CommandDTO& command = commands_queue.pop();
      if (command.stops_run()) {
        is_running = false;
      }
      Protocol::send_command(socket, &command);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}