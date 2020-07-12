#ifndef UNBANK_ITEM_COMMAND_DTO_H
#define UNBANK_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class UnbankItemCommandDTO : public CommandDTO {
 public:
  UnbankItemCommandDTO(const int item);
  UnbankItemCommandDTO(const UnbankItemCommandDTO&) = delete;
  ~UnbankItemCommandDTO();
  int get_id();
  int item;
};

#endif
