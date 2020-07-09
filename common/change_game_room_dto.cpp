#include "change_game_room_dto.h"

ChangeGameRoomDTO::ChangeGameRoomDTO(const int room_number)
    : CommandDTO(), room_number(room_number) {}

ChangeGameRoomDTO::~ChangeGameRoomDTO() {}

int ChangeGameRoomDTO::get_id() { return CHANGE_GAME_ROOM_COMMAND; }
