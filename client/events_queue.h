#ifndef EVENTS_QUEUE_H
#define EVENTS_QUEUE_H

#include <deque>
#include <mutex>

#include "types.h"

class EventsQueue {
 private:
  std::deque<event_t> queue;
  std::mutex block_queue;

 public:
  EventsQueue();
  ~EventsQueue();
  void push(event_t);
  event_t pop();
};

#endif
