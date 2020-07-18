#include "client_notification_sender.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientNotificationSender::ClientNotificationSender(
    Socket& peer_socket,
    BlockingThreadSafeQueue<Notification*>* notifications_queue)
    : peer_socket(peer_socket),
      notifications_queue(notifications_queue),
      alive(true) {}

ClientNotificationSender::~ClientNotificationSender() {
  join();
  // notifications_queue->close();
  delete notifications_queue;
}

void ClientNotificationSender::stop() {
  notifications_queue->close();
  while (!notifications_queue->is_empty()) {
    Notification* n = notifications_queue->pop();
    delete n;
  }

  this->alive = false;
}

void ClientNotificationSender::run() {
  while (alive) {
    // bloquea mientras no haya notificaciones
    if (notifications_queue->is_closed()) break;
    Notification* n = notifications_queue->pop();

    if (n) {
      Protocol::send_notification(this->peer_socket, n);
      delete n;
    }
  }
  std::cout << "notification sender stopped" << std::endl;
}

bool ClientNotificationSender::is_alive() { return this->alive; }
