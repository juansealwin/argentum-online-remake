#include "events_queue.h"

EventsQueue::EventsQueue() {}

EventsQueue::~EventsQueue() {}

void EventsQueue::push(event_t event) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
}

bool EventsQueue::push(event_t event, id_texture_t& item, int& i,
                       bool& is_equipped) {
  std::unique_lock<std::mutex> lock(block_queue);
  // Si no hay items no hay nada que seleccionar
  if (inventory_status[i].first != ID_NULL) {
    item = inventory_status[i].first;
    queue.push_front(event);
    index = i;
    // Para saber si el item esta equipado o no
    is_equipped = inventory_status[i].second;
    return true;
  }
  return false;
}

event_t EventsQueue::pop(int& i) {
  std::unique_lock<std::mutex> lock(block_queue);
  if (queue.empty()) {
    return EVENT_NONE;
  }
  event_t last_event = queue.back();
  queue.pop_back();

  if (last_event == EVENT_SELECT_ITEM) i = index;

  return last_event;
}

void EventsQueue::write_inventory(
    std::map<int, std::pair<id_texture_t, bool>> inventory_updated) {
  std::unique_lock<std::mutex> lock(block_queue);
  inventory_status = inventory_updated;
}

int EventsQueue::append_character(char c) {
  std::unique_lock<std::mutex> lock(block_queue);
  message += c;
  return message.size();
}

int EventsQueue::delete_character() {
  std::unique_lock<std::mutex> lock(block_queue);
  if(message.size())
    message.pop_back();

  return message.size();
}

std::string EventsQueue::read_message() {
  std::unique_lock<std::mutex> lock(block_queue);
  return message;
}