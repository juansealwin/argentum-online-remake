#ifndef MODEL_RECEIVER_H
#define MODEL_RECEIVER_H

#include "thread.h"
#include "blockingqueue.h"

class ModelReceiver : public Thread{
 private:
  BlockingQueue& recived_events;
  bool is_running;

 public:
  ModelReceiver(BlockingQueue&);
  ~ModelReceiver();
  void run();
};


#endif