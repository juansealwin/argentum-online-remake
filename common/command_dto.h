#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include "protocol.h"

class CommandDTO {
 public:
  CommandDTO();
  virtual ~CommandDTO();
  virtual const bool stops_run();
  virtual const int getId();
  CommandDTO(const CommandDTO &) = delete;
};

#endif
