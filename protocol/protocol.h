#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "common_socket.h"

#define LOGIN_COMMAND 1
#define QUIT_COMMAND 2
#define MOVE_COMMAND 3

class CommandDTO;

namespace Protocol {
CommandDTO* receive_command(const Socket& socket);
void send_command(const Socket& socket, CommandDTO* commandDTO);
}  // namespace Protocol

#endif
