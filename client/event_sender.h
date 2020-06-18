#ifndef EVENT_SENDER_H
#define EVENT_SENDER_H

#include "thread.h"
#include "event.h"
#include "blockingqueue.h"
#include <iostream>

class EventSender : public Thread {
 private:
  int id_player;
  BlockingQueue& queue_events;
  //Protocol* courier;
  bool is_running = true;

 public:
  EventSender(int, BlockingQueue&);
  ~EventSender();
  void run();

};



#endif