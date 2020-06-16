#include "protocol.h"

#define REQUEST_LENGTH 4

const std::string Protocol::receiveMessage(const Socket& socket) {
  uint32_t string_size;
  socket.recv(&string_size, REQUEST_LENGTH);
  string_size = ntohl(string_size);
  std::string message(string_size, '\0');
  socket.recv(&message[0], string_size);
  return message;
}

void Protocol::sendMessage(const Socket& socket, const std::string& message) {
  uint32_t size = htonl(message.size());
  socket.send(&size, REQUEST_LENGTH);
  socket.send(&message[0], message.size());
}
