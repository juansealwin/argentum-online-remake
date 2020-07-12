#ifndef GET_BANKED_ITEMS_COMMAND_H
#define GET_BANKED_ITEMS_COMMAND_H

#include "command_dto.h"

class GetBankedItemsCommandDTO : public CommandDTO {
 public:
  GetBankedItemsCommandDTO();
  GetBankedItemsCommandDTO(const GetBankedItemsCommandDTO&) = delete;
  ~GetBankedItemsCommandDTO();
  int get_id();
};

#endif
