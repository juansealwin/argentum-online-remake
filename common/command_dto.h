#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include "protocol.h"

#define LOGIN_COMMAND 1
#define QUIT_COMMAND 2
#define MOVE_COMMAND 3

class CommandDTO {
 public:
  CommandDTO();
  virtual ~CommandDTO();
  virtual bool stops_run() = 0;
  virtual int getId() = 0;
  CommandDTO(const CommandDTO &) = delete;
};

#endif
