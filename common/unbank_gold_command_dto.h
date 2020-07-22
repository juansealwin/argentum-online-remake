#ifndef UNBANK_GOLD_COMMAND_DTO_H
#define UNBANK_GOLD_COMMAND_DTO_H

#include "command_dto.h"

class UnbankGoldCommandDTO : public CommandDTO {
 public:
  explicit UnbankGoldCommandDTO(const int ammount);
  UnbankGoldCommandDTO(const UnbankGoldCommandDTO&) = delete;
  ~UnbankGoldCommandDTO();
  int get_id();
  int ammount;
};

#endif
