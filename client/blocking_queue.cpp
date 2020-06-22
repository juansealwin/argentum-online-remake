#include "blocking_queue.h"

BlockingQueue::BlockingQueue() {}

BlockingQueue::~BlockingQueue() {}

void BlockingQueue::push_event(const Event event) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
  cv.notify_all();
}

Event& BlockingQueue::pop_event() {
  std::unique_lock<std::mutex> lock(block_queue);
  Event last_element;
  while (queue.empty()) {
    cv.wait(lock);
  }
  // If the thread wake up because there won't be more
  // events then it must return
  if (!(more_events) && queue.empty()) {
    last_element.set_request(quit);
    return last_element;
  }
  last_element = queue.back();
  queue.pop_back();
  return last_element;
}

void BlockingQueue::no_more_events() {
  more_events = false;
  cv.notify_all();
}
