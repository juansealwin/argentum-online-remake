#include "event_sender.h"

EventSender::EventSender(int id, BlockingQueue& queue) : id_player(id),queue_events(queue) {}

EventSender::~EventSender() {}

void EventSender::run() {
  try {
    while (is_running) {
      Event event = queue_events.popEvent();
      if (event.isEnding()) is_running = false;
      // courier->sendEvent(event);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}