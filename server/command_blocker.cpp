#include "command_blocker.h"

#include <iostream>
CommandBlocker::CommandBlocker() {
  last_attack_time = last_room_move = std::chrono::high_resolution_clock::now();
}

CommandBlocker::~CommandBlocker() {}

bool CommandBlocker::can_process(CommandDTO* command_dto) {
  int command_id = command_dto->get_id();
  switch (command_id) {
    case ATTACK_COMMAND:
      return can_process_attack();
    case CHANGE_GAME_ROOM_COMMAND:
      return can_process_room_change();
    default:
      return true;
  }
}

bool CommandBlocker::can_process_room_change() {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = std::chrono::duration_cast<std::chrono::seconds>(
      actual_time - last_room_move);
  const int seconds_restriction = 7;
  if (time_difference.count() >= seconds_restriction) {
    last_room_move = actual_time;
    return true;
  }
  return false;
}

bool CommandBlocker::can_process_attack() {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_attack_time;
  const long long nanoseconds = 500000000;
  if (time_difference.count() >= nanoseconds) {  // 62500000) {
    last_attack_time = actual_time;
    return true;
  }
  return false;
}
