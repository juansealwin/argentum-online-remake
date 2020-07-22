#include "private_message_dto.h"

PrivateMessageDTO::PrivateMessageDTO(std::string& dst, std::string& msg)
    : dst(dst), msg(msg) {}

PrivateMessageDTO::~PrivateMessageDTO() {}

std::string PrivateMessageDTO::get_dst() { return dst; }
std::string PrivateMessageDTO::get_msg() { return msg; }

int PrivateMessageDTO::get_id() { return PRIVATE_MESSAGE_COMMAND; }