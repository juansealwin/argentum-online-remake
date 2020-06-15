#include "server_protocol.h"
#include <iostream>

void ServerProtocol::send_response_to_command(const Socket& skt,
                                              const unsigned char* message,
                                              const uint16_t* size) {
  uint16_t size_converted = htons(*size);
  skt.send(&size_converted, 2);
  skt.send(message, *size);
}

unsigned char ServerProtocol::receive_command(const Socket& skt) {
  unsigned char c = 0;
  skt.recv(&c, 1);
  return c;
}

unsigned int ServerProtocol::receive_room_no(const Socket& skt) {
  unsigned char i = 0;
  skt.recv(&i, 1);
  return (unsigned int)i - '0';
}

int ServerProtocol::receive_starting_info(const Socket& skt) {
  Json::Value info;
  info['a'] = "asasas";
  // unsigned char i;
  std::stringstream sbuf;
  msgpack::pack(sbuf, "hola");
  // skt.recv(&i, 1);
  return 5;
}
