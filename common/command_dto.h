#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include "protocol.h"

#define LOGIN_COMMAND 1
#define QUIT_COMMAND 2
#define MOVE_COMMAND 3
#define ATTACK_COMMAND 4
#define PICK_UP_ITEM_COMMAND 5
#define USE_ITEM_COMMAND 6

//typedef enum { LOGIN, QUIT, MOVE, ATTACK, PICK_UP_ITEM } command_t;

class CommandDTO {
 public:
  CommandDTO();
  virtual ~CommandDTO();
  virtual bool stops_run();
  virtual int get_id() = 0;
  CommandDTO(const CommandDTO &) = delete;
};

#endif
