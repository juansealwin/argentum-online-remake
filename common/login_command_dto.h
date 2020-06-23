#ifndef LOGIN_COMMAND_DTO_H
#define LOGIN_COMMAND_DTO_H

#include "command_dto.h"

class LoginCommandDTO : public CommandDTO {
 public:
  explicit LoginCommandDTO(const int room_number);
  LoginCommandDTO(const LoginCommandDTO &) = delete;
  ~LoginCommandDTO();
  bool stops_run();
  int getId();
  const int room_number;
};

#endif
