#ifndef QUIT_COMMAND_DTO_H
#define QUIT_COMMAND_DTO_H

#include "command_dto.h"

class QuitCommandDTO : public CommandDTO {
 public:
  QuitCommandDTO();
  QuitCommandDTO(const QuitCommandDTO &) = delete;
  ~QuitCommandDTO();
  const bool stops_run();
  const int getId();
};

#endif
