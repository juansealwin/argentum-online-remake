#ifndef BANK_ITEM_COMMAND_DTO_H
#define BANK_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class BankItemCommandDTO : public CommandDTO {
 public:
  explicit BankItemCommandDTO(const int item);
  BankItemCommandDTO(const BankItemCommandDTO&) = delete;
  ~BankItemCommandDTO();
  int get_id();
  int item;
};

#endif
