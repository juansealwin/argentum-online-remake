#include "move_command_dto.h"

MoveCommandDTO::MoveCommandDTO(const int player_id,
                               const movement_t movement_type)
    : CommandDTO(), player_id(player_id), movement_type(movement_type) {}

MoveCommandDTO::~MoveCommandDTO() {}

bool MoveCommandDTO::stops_run() { return false; }

int MoveCommandDTO::getId() { return MOVE_COMMAND; }
