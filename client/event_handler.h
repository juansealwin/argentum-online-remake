#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include "blockingqueue.h"
#include "thread.h"

class EventHandler : public Thread {
 private:
  int id_player;
  BlockingQueue& queue_events;
  bool is_running;

 public:
  EventHandler(int, BlockingQueue&);
  ~EventHandler();
  void run();
};

#endif
