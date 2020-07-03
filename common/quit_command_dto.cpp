#include "quit_command_dto.h"

QuitCommandDTO::QuitCommandDTO() : CommandDTO() {}

QuitCommandDTO::~QuitCommandDTO() {}

bool QuitCommandDTO::stops_run() { return true; }

int QuitCommandDTO::get_id() { return QUIT_COMMAND; }
