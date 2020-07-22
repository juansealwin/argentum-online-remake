#ifndef COMMANDS_BLOCKING_QUEUE_H
#define COMMANDS_BLOCKING_QUEUE_H

#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>

#include "command_dto.h"

class CommandsBlockingQueue {
 private:
  std::deque<CommandDTO*> queue;
  std::mutex block_queue;
  std::condition_variable cv;
  bool more_commands = true;

 public:
  CommandsBlockingQueue();
  ~CommandsBlockingQueue();
  void push(CommandDTO* command);
  CommandDTO* pop();
  CommandsBlockingQueue(CommandsBlockingQueue&) = delete;
  CommandsBlockingQueue& operator=(const CommandsBlockingQueue&) = delete;
};

#endif
