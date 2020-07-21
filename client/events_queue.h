#ifndef EVENTS_QUEUE_H
#define EVENTS_QUEUE_H

#include <deque>
#include <map>
#include <mutex>

#include "types.h"
// Es para agregar a ui_status.h y no salte headers recursivos
#include "protected_map.h"

class EventsQueue {
 private:
  std::deque<event_t> queue;
  std::mutex block_queue;
  std::map<int, std::pair<id_texture_t, bool>> inventory_status;
  std::map<int, std::pair<id_texture_t, bool>> shop_status;
  int index;
  std::string message;
  bool open_shop;
  inventory_t shop_type;

 public:
  EventsQueue();
  ~EventsQueue();
  void push(event_t);
  bool select_item(id_texture_t&, int&, bool&);
  bool throwable(id_texture_t&, int&);
  bool get_item(inventory_t&, id_texture_t&, int&);
  event_t pop(int&);
  void write_status(UIStatus&);
  int append_character(char c);
  int delete_character();
  std::string read_message();
  std::string flush_message();
};

#endif
