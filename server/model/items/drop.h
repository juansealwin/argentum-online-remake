#ifndef DROP_H
#define DROP_H
#include "inventory.h"

class Drop {
 public:
  Drop(unsigned int id, unsigned int unique_id, Inventory *inventory, unsigned int gold);
  Drop(unsigned int id, unsigned int unique_id, Item *item, unsigned int gold);
  ~Drop();
  Drop(const Drop &) = delete;
  // si esta vacio, se deberia eliminar
  bool is_empty();
  void add_item(Item *item);
  void add_items(Inventory *inv);
  void add_gold(unsigned int gold);
  Item *take_item(unsigned int position);
  std::size_t size();
  unsigned int take_gold(unsigned int ammount);
  unsigned int ammount_of_gold();
  // id es el type que se le manda al cliente (siempre el mismo
  // para todos los drops)
  unsigned int id;

 private:
 //unique_id es 
  unsigned int gold, unique_id;

  std::vector<Item *> items;
  friend class Serializer;
};
#endif  // DROP_H
