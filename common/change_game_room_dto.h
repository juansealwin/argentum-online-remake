#ifndef CHANGE_GAME_ROOM_DTO_H
#define CHANGE_GAME_ROOM_DTO_H

#include "command_dto.h"

class ChangeGameRoomDTO : public CommandDTO {
 public:
  explicit ChangeGameRoomDTO(const int room_number);
  ChangeGameRoomDTO(const ChangeGameRoomDTO &) = delete;
  ~ChangeGameRoomDTO();
  int get_id();
  const int room_number;
};

#endif
