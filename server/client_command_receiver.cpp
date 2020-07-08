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
  std::cout << "Starting command receiver, hero id: " << hero_id << "at room "
            << current_game_room << " total rooms are " << game_rooms.size()
            << std::endl;
  while (alive) {
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
      delete command_dto;
    } else {
      std::cerr << "Received unknown command or client stopped connection!"
                << std::endl;
      alive = false;
    }
  }
  std::cout << "stopping command receiver" << std::endl;
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
  Protocol::send_notification(peer_socket, create_start_notification());
}

MapChangeNotification *ClientCommandReceiver::create_start_notification() {
  std::vector<unsigned char> notification;
  // mover a la clase
  uint8_t notification_id = 3;
  notification.push_back(notification_id);
  notification.push_back(0);
  return new MapChangeNotification(notification);
}
