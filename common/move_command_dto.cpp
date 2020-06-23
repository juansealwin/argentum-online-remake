#include "move_command_dto.h"

MoveCommandDTO::MoveCommandDTO(const int player_id,
                               const movement_t movement_type)
    : player_id(player_id), movement_type(movement_type) {}

MoveCommandDTO::~MoveCommandDTO() {}

const bool MoveCommandDTO::stops_run() { return false; }

const int MoveCommandDTO::getId() { return MOVE_COMMAND; }
