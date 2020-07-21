#include "events_queue.h"

EventsQueue::EventsQueue() { open_shop = false; }

EventsQueue::~EventsQueue() {}

void EventsQueue::push(event_t event) {
  std::unique_lock<std::mutex> lock(block_queue);
  queue.push_front(event);
}

bool EventsQueue::select_item(id_texture_t& item, int& i, bool& is_equipped) {
  std::unique_lock<std::mutex> lock(block_queue);

  bool selected = false;

  // Si hay un item y no estaba seleccionado, lo seleccionamos
  if (inventory_status[i].first != ID_NULL && i != index) {
    queue.push_front(EVENT_SELECT_ITEM);
    index = i;
  }
  // El item estaba seleccionado
  else if (i == index) {
    // Para saber si el item esta equipado o no
    is_equipped = inventory_status[i].second;
    item = inventory_status[i].first;
    selected = true;
    // Lo deseleccionamos
    queue.push_front(EVENT_SELECT_ITEM);
    // Como no hay más items seleccionado dejamos a index con valor -1
    index = -1;
  }
  return selected;
}

bool EventsQueue::throwable(id_texture_t& item, int& i) {
  std::unique_lock<std::mutex> lock(block_queue);
  bool is_throwable = false;
  if (inventory_status[index].first != ID_NULL &&
      !inventory_status[index].second) {
    i = index;
    item = inventory_status[index].first;
    is_throwable = true;
    // Si lo tiramos lo deseleccionamos
    queue.push_front(EVENT_SELECT_ITEM);
    // Como no hay más items seleccionado dejamos a index con valor -1
    index = -1;
  }

  return is_throwable;
}

bool EventsQueue::get_item_shop(inventory_t& type, id_texture_t& item, int& i) {
  std::unique_lock<std::mutex> lock(block_queue);
  // Si no hay items no hay nada que seleccionar
  if (shop_status[i].first != ID_NULL && open_shop) {
    item = shop_status[i].first;
    type = shop_type;
    return true;
  }
  return false;
}

bool EventsQueue::get_item_inventory(inventory_t& type, id_texture_t& item,
                                     int& i) {
  std::unique_lock<std::mutex> lock(block_queue);
  // Para vender/depositar tiene que estar el shop abierto, tiene que haber item
  // y no tiene que estar equipado
  if (inventory_status[i].first != ID_NULL && open_shop &&
      !inventory_status[i].second) {
    item = inventory_status[i].first;
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
  // Si mercado/banco esta abierto copiamos su estado
  if (open_shop) shop_status = ui.get_shop();
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

bool EventsQueue::is_shop_open() {
  std::unique_lock<std::mutex> lock(block_queue);
  return open_shop;
}