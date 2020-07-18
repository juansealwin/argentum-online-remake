#include "client_listener.h"

#include <iostream>

#include "client_handler.h"
#include "login_command_dto.h"

ClientListener::ClientListener(const char *port,
                               const char *entities_cfg_file) {
  // Socket server_socket;
  server_socket.bind_and_listen(port);
  // this->server_socket = std::move(server_socket);
  std::ifstream entities_file_aux(entities_cfg_file);
  Json::Value entities_cfg;
  entities_file_aux >> entities_cfg;
  const int maps_quantity = entities_cfg["maps"].size();
  for (int i = 0; i < maps_quantity; i++) {
    std::ifstream entities_file(entities_cfg_file);
    std::string map_cfg_file = entities_cfg["maps"][i].asString();
    const char *map_cfg_file_aux = map_cfg_file.c_str();
    std::ifstream map_file(map_cfg_file_aux);

    ThreadSafeQueue<Command *> *commands_queue =
        new ThreadSafeQueue<Command *>();
    Json::Value map_cfg;
    map_file >> map_cfg;
    ArgentumGame *game =
        new ArgentumGame(i, commands_queue, std::ref(map_cfg), entities_file,
                         std::ref(entities_ids), std::ref(message_center));
    game->start();
    game_rooms.emplace_back(game);
    queues_commands.emplace_back(commands_queue);
  }
}

ClientListener::~ClientListener() { join(); }

void ClientListener::stop_listening() {
  for (ArgentumGame *g : game_rooms) {
    g->kill();
    g->join();
    delete g;
  }
  for (ClientHandler *c : clients) {
    delete c;
  }

  for (ThreadSafeQueue<Command *> *q : queues_commands) {
    delete q;
  }
  server_socket.close();
}

StartingInfoNotification *ClientListener::create_start_notification(
    unsigned int hero_id, unsigned int initial_map) {
  std::vector<unsigned char> notification;
  // mover a la clase
  uint8_t notification_id = 2;
  hero_id = htons(hero_id);

  initial_map = htons(initial_map);

  notification.push_back(notification_id);
  notification.resize(notification.size() + sizeof(uint16_t) +
                      sizeof(uint16_t));
  memcpy(notification.data() + 1, &hero_id, sizeof(uint16_t));
  memcpy(notification.data() + 3, &initial_map, sizeof(uint16_t));
  return new StartingInfoNotification(notification);
}

void ClientListener::run() {
  while (true) {
    Socket client_socket;
    try {
      client_socket = this->server_socket.accept();
    } catch (std::invalid_argument) {
      break;
    }
    LoginCommandDTO *login_command = static_cast<LoginCommandDTO *>(
        Protocol::receive_command(client_socket));
    BlockingThreadSafeQueue<Notification *> *notifications_queue =
        new BlockingThreadSafeQueue<Notification *>();
    unsigned int hero_id = game_rooms[login_command->room_number]->add_new_hero(
        login_command->hero_race, login_command->hero_class,
        login_command->player_name);
    message_center.add_player(login_command->player_name, notifications_queue);
    game_rooms[login_command->room_number]->add_notification_queue(
        notifications_queue, hero_id);

    StartingInfoNotification *starting_info =
        create_start_notification(hero_id, login_command->room_number + 1);
    Protocol::send_notification(client_socket, starting_info);
    delete starting_info;
    ClientHandler *client =
        new ClientHandler(std::move(client_socket), login_command->room_number,
                          queues_commands[login_command->room_number],
                          notifications_queue, hero_id, std::ref(game_rooms),
                          login_command->player_name, std::ref(message_center));

    clients.push_back(client);
    // client->start();
    garbage_collector();
    delete login_command;
  }
}

void ClientListener::garbage_collector() {
  std::list<ClientHandler *>::iterator it = clients.begin();
  while (it != clients.end()) {
    if (!(*it)->is_alive()) {
      delete *it;
      it = clients.erase(it);
    } else {
      ++it;
    }
  }
}
