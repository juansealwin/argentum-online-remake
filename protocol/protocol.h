#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "common_socket.h"

namespace Protocol {
const Json::Value receiveMessage(const Socket& socket);
void sendMessage(const Socket& socket, const Json::Value& info);
};  // namespace Protocol

#endif
