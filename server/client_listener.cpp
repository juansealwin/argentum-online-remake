#include "client_listener.h"

#include <iostream>

#include "client_handler.h"
#include "login_command_dto.h"

ClientListener::ClientListener(const char *port, const char *map_cfg_file,
                               const char *entities_cfg_file) {
  Socket server_socket;
  server_socket.bind_and_listen(port);
  this->server_socket = std::move(server_socket);
  // Mover constante a cfg.
  const int x = 1;
  for (int i = 0; i < x; i++) {
    std::ifstream map_file(map_cfg_file);
    std::ifstream entities_file(entities_cfg_file);
    ThreadSafeQueue<Command *> *commands_queue =
        new ThreadSafeQueue<Command *>();
    Json::Value map_cfg;
    map_file >> map_cfg;
    ArgentumGame *game =
        new ArgentumGame(i, commands_queue, std::ref(map_cfg), entities_file, std::ref(entities_ids));
    game->start();
    game_rooms.emplace_back(game);
    queues_commands.emplace_back(commands_queue);
  }
}

ClientListener::~ClientListener() { join(); }

void ClientListener::stop_listening() {
  for (ClientHandler *c : clients) {
    delete c;
  }
  for (ArgentumGame *g : game_rooms) {
    g->kill();
    g->join();
    delete g;
  }
  for (ThreadSafeQueue<Command *> *q : queues_commands) {
    delete q;
  }
  server_socket.close();
}

// agregar mapa en el que este jugando
StartingInfoNotification *ClientListener::create_start_notification(
    unsigned int hero_id) {
  std::vector<unsigned char> notification;
  // mover a la clase
  uint8_t notification_id = 2;
  hero_id = htons(hero_id);
  notification.push_back(notification_id);
  notification.resize(notification.size() + sizeof(uint16_t));
  memcpy(notification.data() + 1, &hero_id, sizeof(uint16_t));
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
    std::cout << "trying to get rno" << std::endl;
    LoginCommandDTO *login_command = static_cast<LoginCommandDTO *>(
        Protocol::receive_command(client_socket));
    std::cout << "room number received: " << login_command->room_number
              << std::endl;
    BlockingThreadSafeQueue<Notification *> *notifications_queue =
        new BlockingThreadSafeQueue<Notification *>();
    // aca a game pasarle la cola de notificaciones para que la agregue de
    // manera segura (con locks) a el vector de notificaciones, si no puede
    // haber race conditions
    unsigned int hero_id = game_rooms[login_command->room_number]->add_new_hero(
        "human", "warrior", "test_name1");
    game_rooms[login_command->room_number]->add_notification_queue(
        notifications_queue, hero_id);

    StartingInfoNotification *starting_info =
        create_start_notification(hero_id);
    Protocol::send_notification(client_socket, starting_info);
    delete starting_info;
    // Protocol::send_notification();
    ClientHandler *client =
        new ClientHandler(std::move(client_socket), login_command->room_number,
                          queues_commands[login_command->room_number],
                          notifications_queue, hero_id, std::ref(game_rooms));

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
      std::cout << "Client is dead!" << std::endl;
      delete *it;
      it = clients.erase(it);
    } else {
      it++;
    }
  }
}
