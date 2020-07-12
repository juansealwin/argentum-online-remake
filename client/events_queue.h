#ifndef EVENTS_QUEUE_H
#define EVENTS_QUEUE_H

#include <deque>
#include <map>
#include <mutex>

#include "types.h"

class EventsQueue {
 private:
  std::deque<event_t> queue;
  std::mutex block_queue;
  std::map<int, std::pair<id_texture_t, bool>> inventory_status;
  int index;
  std::string message;

 public:
  EventsQueue();
  ~EventsQueue();
  void push(event_t);
  bool push(event_t, id_texture_t&, int&, bool&);
  event_t pop(int&);
  void write_inventory(std::map<int, std::pair<id_texture_t, bool>>);
  void append_character(char c);
  void delete_character();
  std::string read_message();
};

#endif
