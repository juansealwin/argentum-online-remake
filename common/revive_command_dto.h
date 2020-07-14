#ifndef REVIVE_COMMAND_DTO
#define REVIVE_COMMAND_DTO

#include "command_dto.h"

class ReviveCommandDTO : public CommandDTO {
 public:
  ReviveCommandDTO();
  ReviveCommandDTO(const ReviveCommandDTO &) = delete;
  ~ReviveCommandDTO();
  bool stops_run() override;
  int get_id();
};

#endif
