#include "events_queue.h"

EventsQueue::EventsQueue() {}

EventsQueue::~EventsQueue() {}

void EventsQueue::push(event_t event) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
}

void EventsQueue::push(event_t event, int i) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
  index = i;
}

event_t EventsQueue::pop(int& i) {
  std::unique_lock<std::mutex> lock(block_queue);
  if (queue.empty()) {
    return EVENT_NONE;
  }
  event_t last_event = queue.back();
  queue.pop_back();

  if(last_event == EVENT_SELECT_ITEM)
    i = index;
    
  return last_event;
}

