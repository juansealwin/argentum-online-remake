#ifndef PICK_UP_COMMAND_DTO
#define PICK_UP_COMMAND_DTO

#include "command_dto.h"

class PickUpCommandDTO : public CommandDTO {
 public:
  PickUpCommandDTO();
  PickUpCommandDTO(const PickUpCommandDTO &) = delete;
  ~PickUpCommandDTO();
  int get_id();
};

#endif
