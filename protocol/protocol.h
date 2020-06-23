#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "command_dto.h"
#include "common_socket.h"

#define LOGIN_COMMAND 1
#define QUIT_COMMAND 2
#define MOVE_COMMAND 3

namespace Protocol {
const CommandDTO* receive_message(const Socket& socket);
void send_message(const Socket& socket, CommandDTO* commandDTO);
};  // namespace Protocol

#endif
