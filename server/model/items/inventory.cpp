#include "inventory.h"

Inventory::Inventory(std::size_t size) { items.reserve(size); }

Inventory::~Inventory() {}

void Inventory::add_item(Item *item) {
  if ((items.size() - items.capacity()) == 0)
    throw ModelException("Inventory is full", "1");
  items.push_back(item);
}