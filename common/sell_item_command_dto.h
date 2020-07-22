#ifndef SELL_ITEM_COMMAND_DTO_H
#define SELL_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class SellItemCommandDTO : public CommandDTO {
 public:
  explicit SellItemCommandDTO(const int item);
  SellItemCommandDTO(const SellItemCommandDTO&) = delete;
  ~SellItemCommandDTO();
  int get_id();
  int item;
};

#endif
