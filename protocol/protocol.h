#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "common_socket.h"

namespace Protocol {
const std::string receiveMessage(const Socket& socket);
void sendMessage(const Socket& socket, const std::string& message);
};  // namespace Protocol

#endif
