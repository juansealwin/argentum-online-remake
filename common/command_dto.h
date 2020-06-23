#ifndef COMMAND_DTO_H
#define COMMAND_DTO_H

#include "protocol.h"

class CommandDTO {
 public:
  CommandDTO();
  virtual ~CommandDTO();
  virtual bool stops_run() = 0;
  virtual int getId() = 0;
  CommandDTO(const CommandDTO &) = delete;
};

#endif
