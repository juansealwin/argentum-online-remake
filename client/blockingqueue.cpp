#include "blockingqueue.h"

BlockingQueue::BlockingQueue() {}

BlockingQueue::~BlockingQueue() {}

void BlockingQueue::pushEvent(const Event event) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
  cv.notify_all();
}

Event& BlockingQueue::popEvent() {
  std::unique_lock<std::mutex> lock(block_queue);
  Event last_element;
  while (queue.empty()) {
    cv.wait(lock);
  }
  // If the thread wake up because there won't be more
  // events then it must return
  if (no_more_events && queue.empty()) {
    last_element.setRequest(quit);
    return last_element;
  }
  last_element = queue.back();
  queue.pop_back();
  return last_element;
}

void BlockingQueue::noMoreEvents() {
  no_more_events = true;
  cv.notify_all();
}
