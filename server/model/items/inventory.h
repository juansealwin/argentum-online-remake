#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"
#include <vector>
#include "model_exceptions.h"
#include <list>
class Item;
class Inventory {
 public:
  //constructores de equipamiento vacio o con items
  Inventory(std::size_t size);
  Inventory();
  ~Inventory();
  Inventory(const Inventory &) = delete;
  void add_item(Item *item);
  bool has_item(unsigned int id);
  Item* remove_item(unsigned int id);
  friend class Serializer;
  private:
  std::vector<Item*> items;

};
#endif  // INVENTORY_H
