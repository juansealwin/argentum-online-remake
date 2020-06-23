#include "client_notification_sender.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientNotificationSender::ClientNotificationSender(
    Socket& peer_socket, ArgentumGame* game,
    BlockingThreadSafeQueue<Notification*>* notifications_queue)
    : game(game),
      peer_socket(peer_socket),
      notifications_queue(notifications_queue) {}

ClientNotificationSender::~ClientNotificationSender() {
  join();
  notifications_queue->close();
  game->clean_notifications_queues();
}

void ClientNotificationSender::stop() { this->alive = false; }

void ClientNotificationSender::run() {
  std::cout << "receiver, game room :" << game->get_room() << std::endl;

  int loops = 0;
  while (alive) {
    /*  Despues de que el protocol este listo:
        //bloquea mientras no haya notificaciones
    Notification *n = notifications_queue->pop();
    Protocol::send_notification(n->vector);
    ver cuando settear alive = false para que se cierre la cola de
    notificaciones
*/

    /*descomentar luego de tests
    Json::Value command = Protocol::receiveMessage(this->peer_socket);*/
    std::string message = "Ganaste";
    const unsigned char* response =
        reinterpret_cast<const unsigned char*>(message.c_str());
    const uint16_t message_length = 7;
    // Protocol::send_response_to_command(this->peer_socket, response,
    //                                    &message_length);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    loops++;
    if (loops == 5) {
      alive = false;
    }
  }
  // de esto se encargaria clienthandler
  // this->peer_socket.close();
}

bool ClientNotificationSender::is_alive() { return this->alive; }
