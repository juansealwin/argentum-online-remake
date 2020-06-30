#include "events_queue.h"

EventsQueue::EventsQueue() {}

EventsQueue::~EventsQueue() {}

void EventsQueue::push(event_t event) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
}

event_t EventsQueue::pop() {
  std::unique_lock<std::mutex> lock(block_queue);
  if (queue.empty()) {
    return EVENT_NONE;
  }
  event_t last_event = queue.back();
  queue.pop_back();
  return last_event;
}

