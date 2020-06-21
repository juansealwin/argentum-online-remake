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
  bool more_events = true;

 public:
  BlockingQueue();
  ~BlockingQueue();
  BlockingQueue(BlockingQueue&) = delete;
  void push_event(const Event);
  Event& pop_event();
  void no_more_events();
  BlockingQueue& operator=(const BlockingQueue&) = delete;
};
#endif
