#include "client_command_receiver.h"

#include <iostream>
#include <sstream>
#include <vector>

  // while (!commands_queue->is_empty()) {
  //   Command *c = commands_queue->pop();
  //   delete c;
  //   if (commands_queue->is_closed()) break;
  // }
  // this->alive = false;

ClientCommandReceiver::ClientCommandReceiver(
    Socket &peer_socket, unsigned int game_room,
    ThreadSafeQueue<Command *> *commands_queue, unsigned int hero_id,
    std::vector<ArgentumGame *> &game_rooms, std::string player_name,
    MessageCenter &message_center)
    : peer_socket(peer_socket),
      current_game_room(game_room),
      commands_queue(commands_queue),
      hero_id(hero_id),
      alive(true),
      sent_quit(false),
      game_rooms(game_rooms),
      player_name(player_name),
      message_center(message_center) {}

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
      //std::cout << "received new command!" << std::endl;
      ChangeGameRoomDTO *cgrDTO =
          dynamic_cast<ChangeGameRoomDTO *>(command_dto);
      if (cgrDTO) {
        if (command_blocker.can_process_room_change())
          change_game_room(cgrDTO->room_number - 1);
        else
          message_center.notify_cant_change_map(player_name);
      } else if (command_blocker.can_process(command_dto)) {
        Command *command = CommandFactory::create_command(command_dto, hero_id);
        commands_queue->push(command);
      }
      if (dynamic_cast<QuitCommandDTO *>(command_dto)) {
        send_close_connection();
        message_center.remove_player(player_name);
        alive = false;
        sent_quit = true;
      }
      delete command_dto;
    } else if (!sent_quit && !commands_queue->is_closed()) {
      alive = false;
      sent_quit = true;
      commands_queue->push(new QuitCommand(hero_id));
    }
  }
}

void ClientCommandReceiver::send_close_connection() {
  std::vector<unsigned char> notification;
  // mover a la clase
  uint8_t notification_id = 0;
  notification.push_back(notification_id);
  CloseConnectionNotification *n =
      new CloseConnectionNotification(notification);
  Protocol::send_notification(peer_socket, n);
  delete n;
}

bool ClientCommandReceiver::is_alive() { return this->alive; }

/********************** metodos privados ********************/

void ClientCommandReceiver::change_game_room(unsigned int new_game_room) {
  if (current_game_room == new_game_room) return;
  std::tuple<Hero *, BlockingThreadSafeQueue<Notification *> *> hero_and_queue =
      game_rooms.at(current_game_room)
          ->remove_hero_and_notification_queue(hero_id);
  game_rooms.at(new_game_room)
      ->add_existing_hero(std::get<0>(hero_and_queue), hero_id);
  game_rooms.at(new_game_room)
      ->add_notification_queue(std::get<1>(hero_and_queue), hero_id);
  commands_queue = game_rooms.at(new_game_room)->get_commands_queue();
  current_game_room = new_game_room;
  MapChangeNotification *n = map_change_notification();
  Protocol::send_notification(peer_socket, n);
  delete n;
}

MapChangeNotification *ClientCommandReceiver::map_change_notification() {
  std::vector<unsigned char> notification;
  // mover a la clase
  uint8_t notification_id = 3;
  notification.push_back(notification_id);
  notification.push_back(current_game_room);
  return new MapChangeNotification(notification);
}
