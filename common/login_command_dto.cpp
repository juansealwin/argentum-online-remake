#include "login_command_dto.h"

LoginCommandDTO::LoginCommandDTO(const int room_number)
    : room_number(room_number) {}

LoginCommandDTO::~LoginCommandDTO() {}

const bool LoginCommandDTO::stops_run() { return false; }

const int LoginCommandDTO::getId() { return LOGIN_COMMAND; }
