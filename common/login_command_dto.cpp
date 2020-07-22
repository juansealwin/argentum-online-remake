#include "login_command_dto.h"

LoginCommandDTO::LoginCommandDTO(const int room_number,
                                 const std::string& player_name,
                                 const std::string& hero_race,
                                 const std::string& hero_class)
    : CommandDTO(),
      room_number(room_number),
      player_name(player_name),
      hero_race(hero_race),
      hero_class(hero_class) {}

LoginCommandDTO::~LoginCommandDTO() {}

int LoginCommandDTO::get_id() { return LOGIN_COMMAND; }
