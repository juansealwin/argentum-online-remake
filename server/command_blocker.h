#ifndef COMMAND_BLOCKER_H
#define COMMAND_BLOCKER_H
#include <chrono>
#include "move_command_dto.h"
#include "command_dto.h"
class CommandBlocker {
 public:
  CommandBlocker();
  ~CommandBlocker();
  CommandBlocker(const CommandBlocker &) = delete;
  bool can_process(CommandDTO *command_dto);
  bool can_process_move();
  bool can_process_attack();

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> last_move_time;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_attack_time;

  
};

#endif  // COMMAND_BLOCKER_H
