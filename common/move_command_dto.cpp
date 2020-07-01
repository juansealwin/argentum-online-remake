#include "move_command_dto.h"

MoveCommandDTO::MoveCommandDTO(const movement_t movement_type)
    : CommandDTO(), movement_type(movement_type) {}

MoveCommandDTO::~MoveCommandDTO() {}

int MoveCommandDTO::get_id() { return MOVE_COMMAND; }
