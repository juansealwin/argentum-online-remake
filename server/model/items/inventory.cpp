#include "inventory.h"

#include <iostream>
Inventory::Inventory(std::size_t size) {
  //std::cout << "new inventory of size " << size << std::endl;
  items.reserve(size);
}

Inventory::~Inventory() {
  std::vector<Item*>::iterator it = items.begin();
  while (it != items.end()) {
    delete *it;
    it = items.erase(it);
  }
}

bool Inventory::is_empty() {
  return (items.size() == 0);
}

void Inventory::add_item(Item* item) {
  // std::cout << "adding new item, inventory size is " << items.size()
  //           << " capacitiy is " << items.capacity() << std::endl;
  if ((items.size() - items.capacity()) == 0)
    throw ModelException("Inventory is full", "1");
  items.push_back(item);
}

bool Inventory::has_item(unsigned int id) {
  using Iter = std::vector<Item*>::const_iterator;
  for (Iter it = items.begin(); it != items.end(); ++it) {
    if ((*it)->id == id) return true;
  }
  return false;
}
bool Inventory::is_full() { return ((items.size() - items.capacity()) == 0); }

Item* Inventory::item_with_id(unsigned int id) {
  using Iter = std::vector<Item*>::const_iterator;
  for (Iter it = items.begin(); it != items.end(); ++it) {
    if ((*it)->id == id) {
      Item* item = (*it);
      return item;
    }
  }
  return nullptr;
}

Item* Inventory::remove_item(unsigned int id) {
  using Iter = std::vector<Item*>::const_iterator;
  for (Iter it = items.begin(); it != items.end(); ++it) {
    if ((*it)->id == id) {
      Item* item = (*it);
      items.erase(it);
      return item;
    }
  }
  return nullptr;
}
