#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>

#include "event.h"

class BlockingQueue {
 private:
  std::deque<Event> queue;
  std::mutex block_queue;
  std::condition_variable cv;
  bool no_more_events = false;

 public:
  BlockingQueue();
  ~BlockingQueue();
  BlockingQueue(BlockingQueue&) = delete;
  void pushEvent(const Event);
  Event& popEvent();
  void noMoreEvents();
  BlockingQueue& operator=(const BlockingQueue&) = delete;
};
#endif
