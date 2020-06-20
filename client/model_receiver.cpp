#include "model_receiver.h"

ModelReceiver::ModelReceiver(BlockingQueue& queue) : recived_events(queue) {
  is_running = true;
}

ModelReceiver::~ModelReceiver() {}

void ModelReceiver::run() {
  try {
    while (is_running) {
      Event event;// = ClientProtocol::getEvent();
      if (event.isEnding()) is_running = false;
        
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}