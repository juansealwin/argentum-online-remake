#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>
template <class T>
class ThreadSafeQueue {
 private:
  std::queue<T> queue;
  mutable std::mutex mutex;
  // std::condition_variable cv;
  bool closed;

 public:
  ThreadSafeQueue()
      : queue(), mutex(), closed(false) {}  // cv(), closed(false) {}

  ~ThreadSafeQueue() {}

  void close() {
    std::lock_guard<std::mutex> lock(mutex);
    closed = true;
    // cv.notify_all();
  }

  void push(T item) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(item);
    // cv.notify_all();
  }

  bool is_empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
  }

  bool is_closed() {
    std::lock_guard<std::mutex> lock(mutex);
    return closed;
  };

  T pop() {
    std::unique_lock<std::mutex> lock(mutex);
    // en el game no me quiero quedar esperando
    // while (queue.empty() && !closed) cv.wait(lock);

    if (closed || queue.empty()) return nullptr;

    T item = queue.front();
    queue.pop();
    return item;
  }
};

template <class T>
class BlockingThreadSafeQueue {
 private:
  std::queue<T> queue;
  mutable std::mutex mutex;
  std::condition_variable cv;
  bool closed;

 public:
  BlockingThreadSafeQueue()
      : queue(), mutex(), closed(false) {}  // cv(), closed(false) {}

  ~BlockingThreadSafeQueue() {}

  void close() {
    std::lock_guard<std::mutex> lock(mutex);
    closed = true;
    cv.notify_all();
  }

  void push(T item) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(item);
    cv.notify_all();
  }

  bool is_empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
  }

  bool is_closed() {
    std::lock_guard<std::mutex> lock(mutex);
    return closed;
  };

  void size() {
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "Notifications queue size is " << (int)queue.size() << std::endl;
  }

  T pop() {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty() && !closed)
      cv.wait(lock);

  	if (queue.empty() && closed)
  		return nullptr;

    T item = queue.front();
    queue.pop();
    return item;
  }
};

#ifndef GAME_COMMANDS_QUEUE
#define GAME_COMMANDS_QUEUE
class Command;
template class ThreadSafeQueue<Command*>;
#endif

#ifndef GAME_NOTIFICATIONS_QUEUE
#define GAME_NOTIFICATIONS_QUEUE
class Notification;
template class BlockingThreadSafeQueue<Notification*>;
#endif

#endif