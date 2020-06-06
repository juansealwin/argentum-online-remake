#include "ClientProtocol.h"
#include <iostream>

void ClientProtocol::send_request
(const Socket& skt, const unsigned char *message, const std::size_t size) {
    skt.send(message, size);
}

std::vector<unsigned char> ClientProtocol::receive_request_response
						  (const Socket& skt) {
    uint16_t message_size;
    skt.recv(&message_size, 2);
    std::vector<unsigned char> message(ntohs(message_size) + 1);
    skt.recv(&message[0], ntohs(message_size));
    message[ntohs(message_size)] = '\0';
    return message;
}
