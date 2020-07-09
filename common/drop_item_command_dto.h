#ifndef DROP_ITEM_COMMAND_DTO_H
#define DROP_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class DropItemCommandDTO : public CommandDTO {
 public:
  DropItemCommandDTO(const int item_id);
  DropItemCommandDTO(const DropItemCommandDTO&) = delete;
  ~DropItemCommandDTO();
  int get_id();
  int item_id;
};

#endif
