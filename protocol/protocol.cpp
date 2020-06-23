#include "protocol.h"

#include <string.h>

#include <iostream>
#include <memory>

#include "login_command_dto.h"
#include "move_command_dto.h"
#include "quit_command_dto.h"

#define ID_LENGTH 1

LoginCommandDTO* receive_login(const Socket& socket) {
  uint16_t room_number;
  socket.recv(&room_number, 2);
  room_number = ntohs(room_number);
  return new LoginCommandDTO(room_number);
}

QuitCommandDTO* receive_quit(const Socket& socket) {
  return new QuitCommandDTO();
}

MoveCommandDTO* receive_move(const Socket& socket) {
  uint16_t player_id, movement_type;
  socket.recv(&player_id, 2);
  socket.recv(&movement_type, 1);
  player_id = ntohs(player_id);
  movement_type = ntohs(movement_type);
  return new MoveCommandDTO(player_id, movement_t(movement_type));
}

CommandDTO* Protocol::receive_command(const Socket& socket) {
  uint16_t command_id;
  socket.recv(&command_id, ID_LENGTH);
  command_id = ntohs(command_id);
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

std::unique_ptr<unsigned char[]> short_int_to_unsigned_char(int number,
                                                            int size) {
  std::unique_ptr<unsigned char[]> message;
  message = std::unique_ptr<unsigned char[]>{new unsigned char[size]};
  uint16_t short_number = htons(static_cast<uint16_t>(number));
  memcpy(&message[0], &short_number, size);
  return message;
}

void send_login(const Socket& socket, const LoginCommandDTO* login_command) {
  std::unique_ptr<unsigned char[]> command_id =
      short_int_to_unsigned_char(LOGIN_COMMAND, ID_LENGTH);
  std::unique_ptr<unsigned char[]> room_number =
      short_int_to_unsigned_char(login_command->room_number, 2);
  socket.send(&command_id, ID_LENGTH);
  socket.send(&room_number, 2);
}

void send_quit(const Socket& socket, const QuitCommandDTO* quit_command) {
  std::unique_ptr<unsigned char[]> command_id =
      short_int_to_unsigned_char(QUIT_COMMAND, ID_LENGTH);
  socket.send(&command_id, ID_LENGTH);
}

void send_move(const Socket& socket, const MoveCommandDTO* move_command) {
  std::unique_ptr<unsigned char[]> command_id =
      short_int_to_unsigned_char(MOVE_COMMAND, ID_LENGTH);
  std::unique_ptr<unsigned char[]> player_id =
      short_int_to_unsigned_char(move_command->player_id, 2);
  std::unique_ptr<unsigned char[]> movement_type =
      short_int_to_unsigned_char(move_command->movement_type, 1);

  socket.send(&command_id, ID_LENGTH);
  socket.send(&player_id, 2);
  socket.send(&movement_type, 1);
}

void Protocol::send_command(const Socket& socket, CommandDTO* commandDTO) {
  switch (commandDTO->getId()) {
    case LOGIN_COMMAND:
      std::cout << "estoy enviando un login\n";
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
