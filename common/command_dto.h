#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include "protocol.h"

// #define LOGIN_COMMAND 1
// #define QUIT_COMMAND 2
// #define MOVE_COMMAND 3
// #define ATTACK_COMMAND 4
// #define PICK_UP_ITEM_COMMAND 5
// #define USE_ITEM_COMMAND 6
// #define CHANGE_GAME_ROOM 7

typedef enum {
  LOGIN_COMMAND = 1,
  QUIT_COMMAND,
  MOVE_COMMAND,
  ATTACK_COMMAND,
  PICK_UP_ITEM_COMMAND,
  USE_ITEM_COMMAND,
  CHANGE_GAME_ROOM_COMMAND,
  DROP_ITEM_COMMAND,
  PRIVATE_MESSAGE_COMMAND,
  BANK_ITEM_COMMAND,
  UNBANK_ITEM_COMMAND,
  BANK_GOLD_COMMAND,
  UNBANK_GOLD_COMMAND,
  GET_BANKED_ITEMS_COMMAND,
  BUY_ITEM_COMMAND,
  SELL_ITEM_COMMAND,
  MEDITATE_COMMAND
} command_t;

class CommandDTO {
 public:
  CommandDTO();
  virtual ~CommandDTO();
  virtual bool stops_run();
  virtual int get_id() = 0;
  CommandDTO(const CommandDTO &) = delete;
};

#endif
