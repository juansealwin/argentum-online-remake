#ifndef USE_ITEM_SPECIAL_DTO
#define USE_ITEM_SPECIAL_DTO

#include "command_dto.h"

class UseItemSpecialCommandDTO : public CommandDTO {
 public:
  UseItemSpecialCommandDTO();
  UseItemSpecialCommandDTO(const UseItemSpecialCommandDTO &) = delete;
  ~UseItemSpecialCommandDTO();
  bool stops_run() override;
  int get_id();
};

#endif
