#ifndef MEDITATE_COMMAND_DTO_H
#define MEDITATE_COMMAND_DTO_H

#include "command_dto.h"

class MeditateCommandDTO : public CommandDTO {
 public:
  MeditateCommandDTO();
  MeditateCommandDTO(const MeditateCommandDTO &) = delete;
  ~MeditateCommandDTO();
  bool stops_run() override;
  int get_id();
};

#endif
