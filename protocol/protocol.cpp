#include "protocol.h"

#define REQUEST_LENGTH 4

const Json::Value Protocol::receiveMessage(const Socket& socket) {
  uint32_t string_size;
  socket.recv(&string_size, REQUEST_LENGTH);
  string_size = ntohl(string_size);
  std::string message(string_size, '\0');
  socket.recv(&message[0], string_size);

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  Json::Value info;
  reader->parse(message.c_str(), message.c_str() + message.size(), &info,
                nullptr);
  delete reader;
  return info;
}

void Protocol::sendMessage(const Socket& socket, const Json::Value& info) {
  Json::FastWriter fastWriter;
  const std::string message = fastWriter.write(info);

  uint32_t size = htonl(message.size());
  socket.send(&size, REQUEST_LENGTH);
  socket.send(&message[0], message.size());
}

void Protocol::send_response_to_command
(const Socket& skt, const unsigned char *message, const uint16_t *size) {
    uint16_t size_converted = htons(*size);
    skt.send(&size_converted, 2);
    skt.send(message, *size);
}

unsigned char Protocol::receive_command(const Socket& skt) {
    unsigned char c = 0;
    skt.recv(&c, 1);
    return c;
}