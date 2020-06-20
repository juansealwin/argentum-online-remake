#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "common_socket.h"

namespace Protocol {
const Json::Value receiveMessage(const Socket& socket);
void sendMessage(const Socket& socket, const Json::Value& info);

void send_response_to_command(const Socket& skt, const unsigned char* message,
                              const uint16_t* size);

unsigned char receive_command(const Socket& skt);

};  // namespace Protocol

#endif
