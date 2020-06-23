#include "inventory.h"
#include <iostream>
Inventory::Inventory(std::size_t size) { items.reserve(size); }

Inventory::~Inventory() {
  std::vector<Item*>::iterator it = items.begin();
  while (it != items.end()) {
    delete *it;
    it = items.erase(it);
  }
}

void Inventory::add_item(Item* item) {
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

Item* Inventory::remove_item(unsigned int id) {
  using Iter = std::vector<Item*>::const_iterator;
  for (Iter it = items.begin(); it != items.end(); ++it) {
    if ((*it)->id == id) {
      Item *item = (*it);
      items.erase(it);
      return item;
    }
  }
  return nullptr;
}
