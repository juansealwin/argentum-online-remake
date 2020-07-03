#include "commands_sender.h"

CommandsSender::CommandsSender(CommandsBlockingQueue& commands_queue,
                               const Socket& socket)
    : commands_queue(commands_queue), socket(socket) {
  is_running = true;
}

CommandsSender::~CommandsSender() {}

void CommandsSender::run() {
  try {
    while (is_running) {
      CommandDTO* command = commands_queue.pop();
      if (command->stops_run()) {
        is_running = false;
      }
      Protocol::send_command(socket, command);
      delete command;
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
