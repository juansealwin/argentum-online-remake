#ifndef HEAL_COMMAND_DTO_H
#define HEAL_COMMAND_DTO_H

#include "command_dto.h"

class HealCommandDTO : public CommandDTO {
 public:
  HealCommandDTO();
  HealCommandDTO(const HealCommandDTO &) = delete;
  ~HealCommandDTO();
  bool stops_run() override;
  int get_id();
};

#endif
