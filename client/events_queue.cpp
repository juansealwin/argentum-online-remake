#include "events_queue.h"

EventsQueue::EventsQueue() {
  open_shop = false;
}

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

bool EventsQueue::get_item(inventory_t& type, id_texture_t& item, int& i) {
  std::unique_lock<std::mutex> lock(block_queue);
  //std::cout<<"ITEM: "<< shop_status[i].first<<std::endl;
  // Si no hay items no hay nada que seleccionar
  if (shop_status[i].first != ID_NULL && open_shop) {
    item = shop_status[i].first;
    type = shop_type;
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

void EventsQueue::write_status(UIStatus& ui) {
  std::unique_lock<std::mutex> lock(block_queue);
  inventory_status = ui.get_items();
  open_shop = ui.is_shop_open(shop_type);
  shop_status.clear();
  if(open_shop)
    shop_status = ui.get_shop();
}

int EventsQueue::append_character(char c) {
  std::unique_lock<std::mutex> lock(block_queue);
  message += c;
  return message.size();
}

int EventsQueue::delete_character() {
  std::unique_lock<std::mutex> lock(block_queue);
  if (message.size()) message.pop_back();

  return message.size();
}

std::string EventsQueue::read_message() {
  std::unique_lock<std::mutex> lock(block_queue);
  return message;
}

std::string EventsQueue::flush_message() {
  std::unique_lock<std::mutex> lock(block_queue);
  std::string temp = message;
  message.clear();

  return temp;
}