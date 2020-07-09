#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientCommandReceiver::ClientCommandReceiver(
    Socket &peer_socket, unsigned int game_room,
    ThreadSafeQueue<Command *> *commands_queue, unsigned int hero_id,
    std::vector<ArgentumGame *> &game_rooms)
    : peer_socket(peer_socket),
      current_game_room(game_room),
      commands_queue(commands_queue),
      hero_id(hero_id),
      alive(true),
      game_rooms(game_rooms) {}

ClientCommandReceiver::~ClientCommandReceiver() { join(); }

void ClientCommandReceiver::stop() { this->alive = false; }

void ClientCommandReceiver::run() {
  while (alive) {
    if (commands_queue->is_closed()) {
      alive = false;
      break;
    }
    CommandDTO *command_dto = Protocol::receive_command(peer_socket);
    if (command_dto != nullptr) {
      ChangeGameRoomDTO *cgrDTO =
          dynamic_cast<ChangeGameRoomDTO *>(command_dto);
      if (cgrDTO) {
        change_game_room(cgrDTO->room_number - 1);
      } else if (command_blocker.can_process(command_dto)) {
        Command *command = CommandFactory::create_command(command_dto, hero_id);
        commands_queue->push(command);
      }
      if (dynamic_cast<QuitCommandDTO *>(command_dto)) {
        send_close_connection();
        alive = false;
      }
      delete command_dto;
    }
  }
 // std::cout << "stopping command receiver" << std::endl;
}

void ClientCommandReceiver::send_close_connection() {

  std::vector<unsigned char> notification;
  // mover a la clase
  uint8_t notification_id = 0;
  notification.push_back(notification_id);
  CloseConnectionNotification* n = new CloseConnectionNotification(notification);
  Protocol::send_notification(peer_socket ,n);
}

bool ClientCommandReceiver::is_alive() { return this->alive; }

/********************** metodos privados ********************/

void ClientCommandReceiver::change_game_room(unsigned int new_game_room) {
  if (current_game_room == new_game_room) return;
  std::cout << "Changing to game game room: " << new_game_room << std::endl;
  std::tuple<Hero *, BlockingThreadSafeQueue<Notification *> *> hero_and_queue =
      game_rooms.at(current_game_room)
          ->remove_hero_and_notification_queue(hero_id);
  game_rooms.at(new_game_room)
      ->add_existing_hero(std::get<0>(hero_and_queue), hero_id);
  game_rooms.at(new_game_room)
      ->add_notification_queue(std::get<1>(hero_and_queue), hero_id);
  commands_queue = game_rooms.at(new_game_room)->get_commands_queue();
  current_game_room = new_game_room;
}
