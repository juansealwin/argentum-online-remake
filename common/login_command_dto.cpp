#include "login_command_dto.h"

LoginCommandDTO::LoginCommandDTO(const int room_number)
    : CommandDTO(), room_number(room_number) {}

LoginCommandDTO::~LoginCommandDTO() {}

bool LoginCommandDTO::stops_run() { return false; }

int LoginCommandDTO::getId() { return LOGIN_COMMAND; }
