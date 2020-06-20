#ifndef MODEL_RECEIVER_H
#define MODEL_RECEIVER_H

#include "thread.h"
#include "blockingmap.h"
#include <map>

class ModelReceiver : public Thread{
 private:
  BlockingMap& blocking_map;
  std::map<int, CharacterStatus> map_updated;
  //ClientProtocol courier;
  bool is_running;

 public:
  ModelReceiver(BlockingMap&);
  ~ModelReceiver();
  void run();
};


#endif