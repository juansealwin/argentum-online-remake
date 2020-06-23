#ifndef INVENTORY_H
#define INVENTORY_H
#include "item.h"
#include <vector>
#include "model_exceptions.h"
class Inventory {
 public:
  //constructores de equipamiento vacio o con items
  Inventory(std::size_t size);
  Inventory();
  ~Inventory();
  Inventory(const Inventory &) = delete;
  void add_item(Item *item);
  private:
  std::vector<Item*> items;

};
#endif  // INVENTORY_H
