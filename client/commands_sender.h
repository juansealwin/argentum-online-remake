#ifndef COMMANDS_SENDER_H
#define COMMANDS_SENDER_H

#include <iostream>

#include "commands_blocking_queue.h"
#include "thread.h"

class CommandsSender : public Thread {
 private:
  CommandsBlockingQueue& commands_queue;
  bool is_running;
  const Socket& socket;

 public:
  CommandsSender(CommandsBlockingQueue& commands_queue, const Socket& socket);
  ~CommandsSender();
  void run();
};

#endif
