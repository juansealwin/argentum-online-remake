#ifndef BUY_ITEM_COMMAND_DTO_H
#define BUY_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class BuyItemCommandDTO : public CommandDTO {
 public:
  explicit BuyItemCommandDTO(const int item);
  BuyItemCommandDTO(const BuyItemCommandDTO&) = delete;
  ~BuyItemCommandDTO();
  int get_id();
  int item;
};

#endif
