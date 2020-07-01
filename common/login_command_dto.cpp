#include "login_command_dto.h"

LoginCommandDTO::LoginCommandDTO(const int room_number)
    : CommandDTO(), room_number(room_number) {}

LoginCommandDTO::~LoginCommandDTO() {}

int LoginCommandDTO::get_id() { return LOGIN_COMMAND; }
