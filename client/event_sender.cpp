#include "event_sender.h"

EventSender::EventSender(int id, BlockingQueue& queue) : id_player(id),queue_events(queue) {}

EventSender::~EventSender() {}

void EventSender::run() {
  try {
    while (is_running) {
      Event event = queue_events.pop_event();
      if (event.is_ending()) is_running = false;
        // ClientProtocol::send_request(/* Aca deberia mandar el evento para que protocol lo serialice*/);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}