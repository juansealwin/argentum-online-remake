#ifndef COMMANDS_SENDER_H
#define COMMANDS_SENDER_H

#include <iostream>

#include "commands_blocking_queue.h"
#include "thread.h"

class CommandsSender : public Thread {
 private:
  const int player_id;
  CommandsBlockingQueue& commands_queue;
  bool is_running = true;
  const Socket& socket;

 public:
  CommandsSender(const int player_id, CommandsBlockingQueue& commands_queue,
                 const Socket& socket);
  ~CommandsSender();
  void run();
};

#endif
