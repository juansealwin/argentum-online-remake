#include "protocol.h"

#include <string.h>

#include <iostream>
#include <memory>
#include <vector>

#include "../server/notifications/notification.h"
#include "attack_command_dto.h"
#include "bank_gold_command_dto.h"
#include "bank_item_command_dto.h"
#include "buy_item_command_dto.h"
#include "change_game_room_dto.h"
#include "drop_item_command_dto.h"
#include "get_banked_items_command_dto.h"
#include "heal_command_dto.h"
#include "login_command_dto.h"
#include "meditate_command_dto.h"
#include "move_command_dto.h"
#include "pick_up_command_dto.h"
#include "private_message_dto.h"
#include "quit_command_dto.h"
#include "revive_command_dto.h"
#include "sell_item_command_dto.h"
#include "unbank_gold_command_dto.h"
#include "unbank_item_command_dto.h"
#include "use_item_command_dto.h"
#include "use_item_special_command_dto.h"
#define ID_LENGTH 1

/********************** COMANDOS ***********************************/

LoginCommandDTO* receive_login(const Socket& socket) {
  uint8_t room_number;
  socket.recv(&room_number, 1);
  return new LoginCommandDTO(room_number);
}

MoveCommandDTO* receive_move(const Socket& socket) {
  uint8_t movement_type;
  socket.recv(&movement_type, 1);
  return new MoveCommandDTO(movement_t(movement_type));
}

UseItemCommandDTO* receive_use_item(const Socket& socket) {
  uint8_t item;
  socket.recv(&item, 1);
  uint8_t item_slot;
  socket.recv(&item_slot, 1);
  uint8_t is_equipped;
  socket.recv(&is_equipped, 1);
  return new UseItemCommandDTO(item, item_slot, is_equipped);
}

ChangeGameRoomDTO* receive_change_game_room(const Socket& socket) {
  uint8_t room_number;
  socket.recv(&room_number, 1);
  return new ChangeGameRoomDTO(room_number);
}

DropItemCommandDTO* receive_drop_item(const Socket& socket) {
  uint8_t item_id;
  socket.recv(&item_id, 1);
  return new DropItemCommandDTO(item_id);
}

std::string receive_string(const Socket& socket) {
  std::vector<unsigned char> vector;
  std::string str;
  uint8_t size = 0;
  socket.recv(&size, 1);
  unsigned char* buffer = new unsigned char[size];
  socket.recv(buffer, size);
  vector = std::vector<unsigned char>(buffer, buffer + size);
  for (auto letter : vector) str += letter;
  delete[] buffer;
  return str;
}

PrivateMessageDTO* receive_private_message(const Socket& socket) {
  std::string dst = receive_string(socket);
  std::string message = receive_string(socket);

  return new PrivateMessageDTO(dst, message);
}

BankItemCommandDTO* receive_bank_item_command(const Socket& socket) {
  uint8_t item = 0;
  socket.recv(&item, 1);
  return new BankItemCommandDTO(item);
}

UnbankItemCommandDTO* receive_unbank_item_command(const Socket& socket) {
  uint8_t item = 0;
  socket.recv(&item, 1);
  return new UnbankItemCommandDTO(item);
}

BankGoldCommandDTO* receive_bank_gold_command(const Socket& socket) {
  uint16_t ammount = 0;
  socket.recv(&ammount, 2);
  return new BankGoldCommandDTO(ammount);
}

UnbankGoldCommandDTO* receive_unbank_gold_command(const Socket& socket) {
  uint16_t ammount = 0;
  socket.recv(&ammount, 2);
  return new UnbankGoldCommandDTO(ammount);
}

BuyItemCommandDTO* receive_buy_command(const Socket& socket) {
  uint8_t item = 0;
  socket.recv(&item, 1);
  return new BuyItemCommandDTO(item);
}

SellItemCommandDTO* receive_sell_command(const Socket& socket) {
  uint8_t item = 0;
  socket.recv(&item, 1);
  return new SellItemCommandDTO(item);
}

CommandDTO* Protocol::receive_command(const Socket& socket) {
  uint8_t command_id;
  int bytes_rcv = socket.recv(&command_id, ID_LENGTH);
  if (bytes_rcv <= 0) return nullptr;  // cerro conexion
  // std::cout << "Command id recibido: " << (int)command_id << std::endl;
  switch (command_id) {
    case LOGIN_COMMAND:
      return receive_login(socket);
    case QUIT_COMMAND:
      return new QuitCommandDTO();
    case MOVE_COMMAND:
      return receive_move(socket);
    case ATTACK_COMMAND:
      return new AttackCommandDTO();
    case PICK_UP_ITEM_COMMAND:
      return new PickUpCommandDTO();
    case USE_ITEM_COMMAND:
      return receive_use_item(socket);
    case CHANGE_GAME_ROOM_COMMAND:
      return receive_change_game_room(socket);
    case DROP_ITEM_COMMAND:
      return receive_drop_item(socket);
    case PRIVATE_MESSAGE_COMMAND:
      return receive_private_message(socket);
    case BANK_ITEM_COMMAND:
      return receive_bank_item_command(socket);
    case UNBANK_ITEM_COMMAND:
      return receive_unbank_item_command(socket);
    case BANK_GOLD_COMMAND:
      return receive_bank_gold_command(socket);
    case UNBANK_GOLD_COMMAND:
      return receive_unbank_gold_command(socket);
    case GET_BANKED_ITEMS_COMMAND:
      return new GetBankedItemsCommandDTO();
    case BUY_ITEM_COMMAND:
      return receive_buy_command(socket);
    case SELL_ITEM_COMMAND:
      return receive_sell_command(socket);
    case MEDITATE_COMMAND:
      return new MeditateCommandDTO();
    case USE_ITEM_SPECIAL_COMMAND:
      return new UseItemSpecialCommandDTO();
    case HEAL_COMMAND:
      return new HealCommandDTO();
    case REVIVE_COMMAND:
      return new ReviveCommandDTO();
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

void send_change_game_room(const Socket& socket,
                           const ChangeGameRoomDTO* change_game_room) {
  uint8_t command_id = CHANGE_GAME_ROOM_COMMAND;
  uint8_t room_number = change_game_room->room_number;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&room_number, 1);
}

void send_quit(const Socket& socket) {
  uint8_t command_id = QUIT_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_move(const Socket& socket, const MoveCommandDTO* move_command) {
  uint8_t command_id = MOVE_COMMAND;
  uint8_t move_type = move_command->movement_type;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&move_type, 1);
}

void send_attack(const Socket& socket) {
  uint8_t command_id = ATTACK_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_pick_up_item(const Socket& socket) {
  uint8_t command_id = PICK_UP_ITEM_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_use_item(const Socket& socket, const UseItemCommandDTO* use_command) {
  uint8_t command_id = USE_ITEM_COMMAND;
  uint8_t item = use_command->item;
  uint8_t item_slot = use_command->item_slot;
  uint8_t is_equipped = use_command->equipped;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, ID_LENGTH);
  socket.send(&item_slot, ID_LENGTH);
  socket.send(&is_equipped, ID_LENGTH);
}

void send_drop_item(const Socket& socket,
                    const DropItemCommandDTO* drop_command) {
  uint8_t command_id = DROP_ITEM_COMMAND;
  uint8_t item = drop_command->item_id;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, ID_LENGTH);
}

void send_string(const Socket& socket, std::string str) {
  // std::cout << "Sending msg: " << str << std::endl;
  std::vector<unsigned char> message;
  message.insert(message.end(), str.begin(), str.end());
  uint8_t msg_size = message.size();
  socket.send(&msg_size, 1);
  socket.send(message.data(), message.size());
}

void send_private_message(const Socket& socket,
                          PrivateMessageDTO* msg_command) {
  uint8_t command_id = PRIVATE_MESSAGE_COMMAND;
  socket.send(&command_id, ID_LENGTH);
  send_string(socket, msg_command->get_dst());
  send_string(socket, msg_command->get_msg());
}

void send_bank_item_command(const Socket& socket,
                            BankItemCommandDTO* commandDTO) {
  uint8_t command_id = BANK_ITEM_COMMAND;
  uint8_t item = commandDTO->item;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, 1);
}

void send_unbank_item_command(const Socket& socket,
                              UnbankItemCommandDTO* commandDTO) {
  uint8_t command_id = UNBANK_ITEM_COMMAND;
  uint8_t item = commandDTO->item;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, 1);
}

void send_bank_gold_command(const Socket& socket,
                            BankGoldCommandDTO* commandDTO) {
  uint8_t command_id = BANK_GOLD_COMMAND;
  uint16_t ammount = commandDTO->ammount;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&ammount, 2);
}

void send_unbank_gold_command(const Socket& socket,
                              UnbankGoldCommandDTO* commandDTO) {
  uint8_t command_id = UNBANK_GOLD_COMMAND;
  uint16_t ammount = commandDTO->ammount;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&ammount, 2);
}

void send_get_banked_items_command(const Socket& socket,
                                   GetBankedItemsCommandDTO*) {
  uint8_t command_id = GET_BANKED_ITEMS_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_buy_command(const Socket& socket, BuyItemCommandDTO* commandDTO) {
  uint8_t command_id = BUY_ITEM_COMMAND;
  uint8_t item = commandDTO->item;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, 1);
}

void send_sell_command(const Socket& socket, SellItemCommandDTO* commandDTO) {
  uint8_t command_id = SELL_ITEM_COMMAND;
  uint8_t item = commandDTO->item;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, 1);
}

void send_revive_command(const Socket& socket) {
  uint8_t command_id = REVIVE_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_heal_command(const Socket& socket) {
  uint8_t command_id = HEAL_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_use_special_command(const Socket& socket) {
  uint8_t command_id = USE_ITEM_SPECIAL_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_meditate_command(const Socket& socket) {
  uint8_t command_id = MEDITATE_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}


void Protocol::send_command(const Socket& socket, CommandDTO* commandDTO) {
  switch (commandDTO->get_id()) {
    case LOGIN_COMMAND:
      send_login(socket, dynamic_cast<LoginCommandDTO*>(commandDTO));
      break;

    case QUIT_COMMAND:
      send_quit(socket);
      break;

    case MOVE_COMMAND:
      send_move(socket, dynamic_cast<MoveCommandDTO*>(commandDTO));
      break;

    case ATTACK_COMMAND:
      send_attack(socket);
      break;
    
    case PICK_UP_ITEM_COMMAND:
      send_pick_up_item(socket);
      break;
    
    case USE_ITEM_COMMAND:
      send_use_item(socket, dynamic_cast<UseItemCommandDTO*>(commandDTO));
      break;
    
    case CHANGE_GAME_ROOM_COMMAND:
      send_change_game_room(socket,
                            dynamic_cast<ChangeGameRoomDTO*>(commandDTO));
      break;
    
    case DROP_ITEM_COMMAND:
      send_drop_item(socket, dynamic_cast<DropItemCommandDTO*>(commandDTO));
      break;
    
    case PRIVATE_MESSAGE_COMMAND:
      send_private_message(socket,
                           dynamic_cast<PrivateMessageDTO*>(commandDTO));
      break;

    case BANK_ITEM_COMMAND:
      send_bank_item_command(socket,
                             dynamic_cast<BankItemCommandDTO*>(commandDTO));
      break;

    case UNBANK_ITEM_COMMAND:
      send_unbank_item_command(socket,
                               dynamic_cast<UnbankItemCommandDTO*>(commandDTO));
      break;

    case BANK_GOLD_COMMAND:
      send_bank_gold_command(socket,
                             dynamic_cast<BankGoldCommandDTO*>(commandDTO));
      break;

    case UNBANK_GOLD_COMMAND:
      send_unbank_gold_command(socket,
                               dynamic_cast<UnbankGoldCommandDTO*>(commandDTO));
      break;

    case GET_BANKED_ITEMS_COMMAND:
      send_get_banked_items_command(
          socket, dynamic_cast<GetBankedItemsCommandDTO*>(commandDTO));
      break;
    
    case BUY_ITEM_COMMAND:
      send_buy_command(socket, dynamic_cast<BuyItemCommandDTO*>(commandDTO));
      break;

    case SELL_ITEM_COMMAND:
      send_sell_command(socket, dynamic_cast<SellItemCommandDTO*>(commandDTO));
      break;

    case MEDITATE_COMMAND:
      send_meditate_command(socket);
      break;

    case REVIVE_COMMAND:
      send_revive_command(socket);
      break;

    case HEAL_COMMAND:
      send_heal_command(socket);
      break;

    case USE_ITEM_SPECIAL_COMMAND:
      send_use_special_command(socket);
      break;

    default:
      break;
  }
  // delete commandDTO;
}

/********************** NOTIFICACIONES ***********************************/

void Protocol::send_notification(const Socket& socket, Notification* n) {
  std::vector<unsigned char> serialization = n->vector;
  uint16_t size = htons(serialization.size());
  socket.send(&size, 2);
  socket.send(serialization.data(), serialization.size());
}

// Definir que devuelve la clase (Puede moverse la notificacion que tengo en el
// server a protocol/common y usar eso)
void Protocol::receive_notification(const Socket& socket,
                                    std::vector<unsigned char>& vector) {
  uint16_t notification_size = 0;
  socket.recv(&notification_size, 2);
  notification_size = ntohs(notification_size);
  unsigned char* buffer = new unsigned char[notification_size];
  socket.recv(buffer, notification_size);
  vector = std::vector<unsigned char>(buffer, buffer + notification_size);
  delete[] buffer;
}