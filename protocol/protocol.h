#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include "common_socket.h"

class Notification;
class CommandDTO;

namespace Protocol {
CommandDTO* receive_command(const Socket& socket);
void send_command(const Socket& socket, CommandDTO* commandDTO);
void send_notification(const Socket& socket, Notification* n);
//devuelve cantidad de bytes recibidos
int receive_notification(const Socket& socket, std::vector<unsigned char>&);
}  // namespace Protocol

#endif
