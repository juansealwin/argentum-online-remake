#ifndef EVENTS_QUEUE_H
#define EVENTS_QUEUE_H

#include <deque>
#include <mutex>

#include "types.h"

class EventsQueue {
 private:
  std::deque<event_t> queue;
  std::mutex block_queue;
  int index;

 public:
  EventsQueue();
  ~EventsQueue();
  void push(event_t);
  void push(event_t, int);
  event_t pop(int&);
};

#endif
