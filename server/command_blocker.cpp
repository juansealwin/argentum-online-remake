#include "command_blocker.h"

CommandBlocker::CommandBlocker() {
  last_move_time = std::chrono::high_resolution_clock::now();
}

CommandBlocker::~CommandBlocker() {}

bool CommandBlocker::can_process(CommandDTO* command_dto) {
  int command_id = command_dto->get_id();
  switch (command_id) {
    case MOVE_COMMAND:
      return can_process_move();
    default:
      return true;
  }
}

bool CommandBlocker::can_process_move() {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_move_time;
  const long long nanoseconds = 60000000;
  if (time_difference.count() >= nanoseconds) {//62500000) {
    last_move_time = actual_time;
    return true;
  }
  return false;
}
