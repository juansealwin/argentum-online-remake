#ifndef COMMAND_BLOCKER_H
#define COMMAND_BLOCKER_H
#include <chrono>

#include "command_dto.h"
#include "move_command_dto.h"
class CommandBlocker {
 public:
  CommandBlocker(const int seconds_for_proccesing_room_changes,
                 const int nanoseconds_for_proccesing_attacks);
  ~CommandBlocker();
  CommandBlocker(const CommandBlocker &) = delete;
  bool can_process(CommandDTO *command_dto);
  bool can_process_attack();
  bool can_process_room_change();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_attack_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_room_move;
  int seconds_for_proccesing_room_changes;
  int nanoseconds_for_proccesing_attacks;
};

#endif  // COMMAND_BLOCKER_H
