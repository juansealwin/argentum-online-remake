#ifndef DROP_H
#define DROP_H
#include "inventory.h"

class Drop {
 public:
  Drop(Inventory *inventory, unsigned int gold);
  Drop(Item *item, unsigned int gold);
  ~Drop();
  Drop(const Drop &) = delete;
  // si esta vacio, se deberia eliminar
  bool is_empty();
  void add_item(Item *item);
  Item *take_item(unsigned int position);
  std::size_t size();
  unsigned int take_gold(unsigned int ammount);
  unsigned int ammount_of_gold();

 private:
  // id es el type que se le manda al cliente (siempre el mismo
  // para todos los drops)
  unsigned int id, gold;
  
  std::vector<Item *> items;
};
#endif  // DROP_H
