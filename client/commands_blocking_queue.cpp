#include "commands_blocking_queue.h"

#include "quit_command_dto.h"

CommandsBlockingQueue::CommandsBlockingQueue() {}

CommandsBlockingQueue::~CommandsBlockingQueue() {}

void CommandsBlockingQueue::push(CommandDTO* command) {
  std::unique_lock<std::mutex> lock(block_queue);
  std::cout << "pusheo comando\n";
  queue.push_front(command);
  cv.notify_all();
}

CommandDTO* CommandsBlockingQueue::pop() {
  std::unique_lock<std::mutex> lock(block_queue);
  while (queue.empty()) {
    cv.wait(lock);
  }

  if (!more_commands && queue.empty()) {
    return new QuitCommandDTO();
  }
  CommandDTO* last_element = queue.back();
  queue.pop_back();
  return last_element;
}

void CommandsBlockingQueue::no_more_commands() {
  more_commands = false;
  cv.notify_all();
}
