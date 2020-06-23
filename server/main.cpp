
#include <iostream>
#include "inventory.h"
#include "item.h"
#include "weapon.h"
#include "staff.h"
int main() {
  Inventory inventory(5);
  Weapon *w1 = new Weapon(1,5,5,5);
  Weapon *w2 = new Weapon(2,5,5,5);
  Weapon *w3 = new Weapon(3,5,5,5);
  Weapon *w4 = new Weapon(4,5,5,5);
  Weapon *w5 = new Weapon(5,5,5,5);
  inventory.add_item(w1);
  inventory.add_item(w2);
  inventory.add_item(w3);
  inventory.add_item(w4);
  inventory.add_item(w5);
  //inventory.add_item(s);
  std::cout <<"Goodbye" <<std::endl;
  std::cout << "inventory has item: 1?: " << inventory.has_item(1) << std::endl;
  std::cout << "inventory has item: 1?: " << inventory.has_item(1) << std::endl;
  Item *item_removido = inventory.remove_item(2);
  std::cout << "id item removido: " << item_removido->id << std::endl;
  delete item_removido;
  std::cout << "inventory has item: 1?: " << inventory.has_item(1) << std::endl;
}
