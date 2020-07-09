#include "drop.h"

Drop::Drop(unsigned int id, unsigned int unique_id, Inventory *inventory,
           unsigned int gold)
    : id(id), unique_id(unique_id), gold(gold) {
  std::cout << "created drop with id " << unique_id << std::endl;
  add_items(inventory);
  // items.insert(items.end(), std::make_move_iterator(inventory->items.begin()),
  //              std::make_move_iterator(inventory->items.end()));
  // inventory->items.erase(inventory->items.begin(), inventory->items.end());
}

Drop::Drop(unsigned int id, unsigned int unique_id, Item *item,
           unsigned int gold)
    : id(id), unique_id(unique_id), gold(gold) {
  std::cout << "created drop with id " << unique_id << std::endl;
  items.push_back(item);
}

Drop::~Drop() {
  std::vector<Item *>::iterator it = items.begin();
  while (it != items.end()) {
    delete *it;
    it = items.erase(it);
  }
}

std::size_t Drop::size() { return items.size(); }
bool Drop::is_empty() { return ((items.size() == 0) && (gold == 0)); }

void Drop::add_item(Item *item) { items.push_back(item); }

void Drop::add_items(Inventory *inv) {
  items.insert(items.end(), std::make_move_iterator(inv->items.begin()),
               std::make_move_iterator(inv->items.end()));
  inv->items.erase(inv->items.begin(), inv->items.end());
}

void Drop::add_gold(unsigned int gold) { this->gold += gold; }

Item *Drop::take_item(unsigned int index) {
  Item *item = items.at(index - 1);
  items.erase(items.begin() + index - 1);
  return item;
}

unsigned int Drop::ammount_of_gold() { return gold; }

unsigned int Drop::take_gold(unsigned int ammount) {
  unsigned int ammount_to_take = std::min(gold, ammount);
  gold -= ammount_to_take;
  return ammount_to_take;
}