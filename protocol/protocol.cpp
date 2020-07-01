#include "protocol.h"

#include <string.h>

#include <iostream>
#include <memory>
#include <vector>

#include "../server/notifications/notification.h"
#include "login_command_dto.h"
#include "move_command_dto.h"
#include "quit_command_dto.h"
#define ID_LENGTH 1

/********************** COMANDOS ***********************************/

LoginCommandDTO* receive_login(const Socket& socket) {
  uint8_t room_number;
  socket.recv(&room_number, 1);
  std::cout << "room number: " << (int)room_number << std::endl;
  return new LoginCommandDTO(room_number);
}

QuitCommandDTO* receive_quit(const Socket& socket) {
  // deshabilito temporalmente
  // return new QuitCommandDTO();
  return nullptr;
}

MoveCommandDTO* receive_move(const Socket& socket) {
  uint8_t movement_type;
  socket.recv(&movement_type, 1);
  return new MoveCommandDTO(movement_t(movement_type));
}

CommandDTO* Protocol::receive_command(const Socket& socket) {
  uint8_t command_id;
  int bytes_rcv = socket.recv(&command_id, ID_LENGTH);
  if (bytes_rcv <= 0) return nullptr;  // cerro conexion
  std::cout << "Command id recibido: " << (int)command_id << std::endl;
  switch (command_id) {
    case LOGIN_COMMAND:
      return receive_login(socket);
    case QUIT_COMMAND:
      return receive_quit(socket);
    case MOVE_COMMAND:
      return receive_move(socket);
    default:
      return nullptr;
  }
}

void send_login(const Socket& socket, const LoginCommandDTO* login_command) {
  uint8_t command_id = LOGIN_COMMAND;
  uint8_t room_number = login_command->room_number;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&room_number, 1);
}

void send_quit(const Socket& socket, const QuitCommandDTO* quit_command) {
  uint8_t command_id = QUIT_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_move(const Socket& socket, const MoveCommandDTO* move_command) {
  uint8_t command_id = MOVE_COMMAND;
  uint8_t move_type = move_command->movement_type;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&move_type, 1);
}

void Protocol::send_command(const Socket& socket, CommandDTO* commandDTO) {
  switch (commandDTO->getId()) {
    case LOGIN_COMMAND:
      send_login(socket, static_cast<LoginCommandDTO*>(commandDTO));
      break;
    case QUIT_COMMAND:
      send_quit(socket, static_cast<QuitCommandDTO*>(commandDTO));
      break;
    case MOVE_COMMAND:
      send_move(socket, static_cast<MoveCommandDTO*>(commandDTO));
      break;
    default:
      break;
  }
}

/********************** NOTIFICACIONES ***********************************/

void Protocol::send_notification(const Socket& socket, Notification* n) {
  std::vector<unsigned char> serialization = n->vector;
  uint16_t size = htons(serialization.size());
  socket.send(&size, 2);
  socket.send(serialization.data(), serialization.size());
}

// para mostrar lo que se recibe, descomentar este template y todo lo comentado
// en receive_notifation

template <typename T>
T extract(const std::vector<unsigned char>& v, int pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  return value;
}

// Definir que devuelve la clase (Puede moverse la notificacion que tengo en el
// server a protocol/common y usar eso)
void Protocol::receive_notification(const Socket& socket,
                                    std::vector<unsigned char>& vector) {
  uint16_t notification_size = 0;
  socket.recv(&notification_size, 2);
  notification_size = ntohs(notification_size);
  unsigned char buffer[notification_size];
  socket.recv(buffer, notification_size);
  vector = std::vector<unsigned char>(buffer, buffer + notification_size);
  // std::vector<unsigned char> vector = std::vector<unsigned char>(buffer,
  // buffer + notification_size);
  int j = 1;
  while (j < vector.size()) {
    uint16_t id = ntohs(extract<uint16_t>(vector, j));
    j += 2;
    int entity_type = (int)vector.at(j);
    j++;
    int x = (int)vector.at(j);
    j++;
    int y = (int)vector.at(j);
    j++;
  }
}