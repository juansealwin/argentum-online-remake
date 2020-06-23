#include "quit_command_dto.h"

QuitCommandDTO::QuitCommandDTO() {}

QuitCommandDTO::~QuitCommandDTO() {}

const bool QuitCommandDTO::stops_run() { return true; }

const int QuitCommandDTO::getId() { return QUIT_COMMAND; }
