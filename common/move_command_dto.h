#ifndef MOVE_COMMAND_DTO_H
#define MOVE_COMMAND_DTO_H

#include "command_dto.h"

typedef enum {
  move_down,
  move_up,
  move_left,
  move_right,
  stop_move
} movement_t;

class MoveCommandDTO : public CommandDTO {
 public:
  MoveCommandDTO(const movement_t movement_type);
  MoveCommandDTO(const MoveCommandDTO &) = delete;
  ~MoveCommandDTO();
  int get_id();
  const movement_t movement_type;
};

#endif
