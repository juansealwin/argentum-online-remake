#include "command_blocker.h"

#include <iostream>
CommandBlocker::CommandBlocker(const int seconds_for_proccesing_room_changes,
                               const int nanoseconds_for_proccesing_attacks)
    : seconds_for_proccesing_room_changes(seconds_for_proccesing_room_changes),
      nanoseconds_for_proccesing_attacks(nanoseconds_for_proccesing_attacks) {
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
  if (time_difference.count() >= seconds_for_proccesing_room_changes) {
    last_room_move = actual_time;
    return true;
  }
  return false;
}

bool CommandBlocker::can_process_attack() {
  auto actual_time = std::chrono::high_resolution_clock::now();
  auto time_difference = actual_time - last_attack_time;
  if (time_difference.count() >= nanoseconds_for_proccesing_attacks) {
    last_attack_time = actual_time;
    return true;
  }
  return false;
}
