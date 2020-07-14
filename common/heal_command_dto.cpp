#include "heal_command_dto.h"

HealCommandDTO::HealCommandDTO() : CommandDTO() {}

HealCommandDTO::~HealCommandDTO() {}

bool HealCommandDTO::stops_run() { return false; }

int HealCommandDTO::get_id() { return HEAL_COMMAND; }
