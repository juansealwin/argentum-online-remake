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

    //bloquea mientras no haya notificaciones
    Notification *n = notifications_queue->pop();
    Protocol::send_notification(this->peer_socket ,n);
    //ver cuando settear alive = false para que se cierre la cola de
    //notificaciones
    delete n;
  }

}

bool ClientNotificationSender::is_alive() { return this->alive; }
