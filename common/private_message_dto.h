#ifndef PRIVATE_MESSAGE_DTO
#define PRIVATE_MESSAGE_DTO

#include "command_dto.h"

class PrivateMessageDTO : public CommandDTO {
 public:
  PrivateMessageDTO(std::string dst, std::string msg);
  PrivateMessageDTO(const PrivateMessageDTO &) = delete;
  ~PrivateMessageDTO();
  int get_id();
  std::string get_dst();
  std::string get_msg();
 private:
  std::string dst;
  std::string msg;
};

#endif
