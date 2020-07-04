#include "drop.h"

Drop::Drop(Inventory *inventory) {
  items.insert(items.end(), std::make_move_iterator(inventory->items.begin()), 
                    std::make_move_iterator(inventory->items.end()));
  inventory->items.erase(inventory->items.begin(), inventory->items.end());
}

Drop::~Drop() {
  std::vector<Item*>::iterator it = items.begin();
  while (it != items.end()) {
    delete *it;
    it = items.erase(it);
  }
}

std::size_t Drop::size() {
  return items.size();
}
bool Drop::is_empty() {
  return (items.size() == 0);
}

void Drop::add_item(Item *item) {
  items.push_back(item);
}

Item* Drop::take_item(unsigned int index) {
  Item *item = items.at(index - 1);
  items.erase(items.begin() + index - 1);
  return item;
}