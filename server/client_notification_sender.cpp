#include "client_notification_sender.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientNotificationSender::ClientNotificationSender(Socket& peer_socket,
                                                   ArgentumGame* game)
    : game(game), peer_socket(peer_socket) {}

ClientNotificationSender::~ClientNotificationSender() {
  // std::cout << "trying to join cliente sender" << std::endl;
  join();
  //  std::cout << "joined client sender" << std::endl;
}

void ClientNotificationSender::stop() { this->alive = false; }

void ClientNotificationSender::run() {
  std::cout << "receiver, game room :" << game->get_room() << std::endl;

  int loops = 0;
  while (alive) {
    std::cout << "In sender thread" << std::endl;
    /*descomentar luego de tests
    Json::Value command = Protocol::receiveMessage(this->peer_socket);*/
    std::string message = "Ganaste";
    const unsigned char* response =
        reinterpret_cast<const unsigned char*>(message.c_str());
    const uint16_t message_length = 7;
    Protocol::send_response_to_command(this->peer_socket, response,
                                       &message_length);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    loops++;
    if (loops == 5) {
      alive = false;
      std::cout << "alive was set to false" << std::endl;
      std::cout << "finishing notif sender run()";
    }
  }
  // de esto se encargaria clienthandler
  // this->peer_socket.close();
}

bool ClientNotificationSender::is_alive() { return this->alive; }
