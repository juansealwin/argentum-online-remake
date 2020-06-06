#include "ServerProtocol.h"
#include <iostream>

void ServerProtocol::send_response_to_command
(const Socket& skt, const unsigned char *message, const uint16_t *size) {
    uint16_t size_converted = htons(*size);
    skt.send(&size_converted, 2);
    skt.send(message, *size);
}

unsigned char ServerProtocol::receive_command(const Socket& skt) {
    unsigned char c = 0;
    skt.recv(&c, 1);
    return c;
}
