#include "drop.h"

Drop::Drop(Inventory *inventory, unsigned int coins) : coins(coins) {
  items.insert(items.end(), std::make_move_iterator(inventory->items.begin()),
               std::make_move_iterator(inventory->items.end()));
  inventory->items.erase(inventory->items.begin(), inventory->items.end());
}

Drop::Drop(Item *item, unsigned int coins) : coins(coins) { items.push_back(item); }

Drop::~Drop() {
  std::vector<Item *>::iterator it = items.begin();
  while (it != items.end()) {
    delete *it;
    it = items.erase(it);
  }
}

std::size_t Drop::size() { return items.size(); }
bool Drop::is_empty() { return ((items.size() == 0) && (coins == 0)); }

void Drop::add_item(Item *item) { items.push_back(item); }

Item *Drop::take_item(unsigned int index) {
  Item *item = items.at(index - 1);
  items.erase(items.begin() + index - 1);
  return item;
}

unsigned int Drop::ammount_of_coins() {
  return coins;
}

unsigned int Drop::take_coins(unsigned int ammount) {
  coins -= ammount;
  return ammount;
}