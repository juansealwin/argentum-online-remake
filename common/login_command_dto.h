#ifndef LOGIN_COMMAND_DTO_H
#define LOGIN_COMMAND_DTO_H

#include <string>

#include "command_dto.h"

class LoginCommandDTO : public CommandDTO {
 public:
  explicit LoginCommandDTO(const int room_number, const std::string& player_name,
                           const std::string& hero_race,
                           const std::string& hero_class);
  LoginCommandDTO(const LoginCommandDTO &) = delete;
  ~LoginCommandDTO();
  int get_id();
  const int room_number;
  const std::string player_name;
  const std::string hero_race;
  const std::string hero_class;
};

#endif
