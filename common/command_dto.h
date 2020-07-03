#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include "protocol.h"

#define LOGIN_COMMAND 1
#define QUIT_COMMAND 2
#define MOVE_COMMAND 3
#define ATTACK_COMMAND 4

typedef enum { LOGIN, QUIT, MOVE, ATTACK } command_t;

class CommandDTO {
 public:
  CommandDTO();
  virtual ~CommandDTO();
  virtual bool stops_run();
  virtual int get_id() = 0;
  CommandDTO(const CommandDTO &) = delete;
};

#endif
