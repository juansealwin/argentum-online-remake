#include "revive_command_dto.h"

ReviveCommandDTO::ReviveCommandDTO() : CommandDTO() {}

ReviveCommandDTO::~ReviveCommandDTO() {}

bool ReviveCommandDTO::stops_run() { return false; }

int ReviveCommandDTO::get_id() { return REVIVE_COMMAND; }
