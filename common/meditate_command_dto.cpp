#include "meditate_command_dto.h"

MeditateCommandDTO::MeditateCommandDTO() : CommandDTO() {}

MeditateCommandDTO::~MeditateCommandDTO() {}

bool MeditateCommandDTO::stops_run() { return false; }

int MeditateCommandDTO::get_id() { return MEDITATE_COMMAND; }
