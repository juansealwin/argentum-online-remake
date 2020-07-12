#ifndef BANK_GOLD_COMMAND_DTO_H
#define BANK_GOLD_COMMAND_DTO_H

#include "command_dto.h"

class BankGoldCommandDTO : public CommandDTO {
 public:
  BankGoldCommandDTO(const int ammount);
  BankGoldCommandDTO(const BankGoldCommandDTO&) = delete;
  ~BankGoldCommandDTO();
  int get_id();
  int ammount;
};

#endif
