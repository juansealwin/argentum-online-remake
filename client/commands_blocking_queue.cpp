#include "commands_blocking_queue.h"

#include "quit_command_dto.h"

CommandsBlockingQueue::CommandsBlockingQueue() {}

CommandsBlockingQueue::~CommandsBlockingQueue() {}

void CommandsBlockingQueue::push(CommandDTO* command) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(command);
  cv.notify_all();
}

CommandDTO* CommandsBlockingQueue::pop() {
  std::unique_lock<std::mutex> lock(block_queue);
  while (queue.empty()) {
    cv.wait(lock);
  }
  CommandDTO* last_element = queue.back();
  queue.pop_back();
  return last_element;
}