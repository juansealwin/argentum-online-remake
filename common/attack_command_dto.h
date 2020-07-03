#ifndef ATTACK_COMMAND_DTO_H
#define ATTACK_COMMAND_DTO_H

#include "command_dto.h"

class AttackCommandDTO : public CommandDTO {
 public:
  AttackCommandDTO();
  AttackCommandDTO(const AttackCommandDTO &) = delete;
  ~AttackCommandDTO();
  int get_id();
};

#endif
