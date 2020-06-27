#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "common_socket.h"

#define LOGIN_COMMAND 1
#define QUIT_COMMAND 2
#define MOVE_COMMAND 3
class Notification;
class CommandDTO;

namespace Protocol {
CommandDTO* receive_command(const Socket& socket);
void send_command(const Socket& socket, CommandDTO* commandDTO);
void send_notification(const Socket& socket, Notification* n);
void receive_notification(const Socket& socket);
}  // namespace Protocol

#endif
