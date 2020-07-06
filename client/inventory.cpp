#include "inventory.h"

Inventory::Inventory() {
  for (int i = 0; i < MAX_ITEMS; i++) {
    items[i] = ID_NULL;
  }
  gold = 0;
}

Inventory::Inventory(int new_gold) {
  for (int i = 0; i < MAX_ITEMS; i++) {
    items[i] = ID_NULL;
  }
  gold = new_gold;
}

Inventory::~Inventory() {}

Inventory& Inventory::operator=(const Inventory& other_inv) {
  gold = other_inv.gold;
  for (int i = 0; i < MAX_ITEMS; i++) {
    add_item(other_inv.items[i], i);
  }
  return *this;
}

void Inventory::add_item(id_texture_t new_item) {
  int i = 0;
  while ((items[i] != ID_NULL)) {
    i++;
  }
  items[i] = new_item;
}

void Inventory::add_item(id_texture_t new_item, int i) { items[i] = new_item; }

id_texture_t Inventory::drop_item(int index) {
  id_texture_t temp = ID_NULL;

  if (items[index] != ID_NULL) {
    temp = items[index];
    items[index] = ID_NULL;
  }
  return temp;
}

void Inventory::change_gold(int income) { gold = income; }

void Inventory::render(SDL_Renderer* renderer, bool is_selected, int index) {
  int j = X_INVENTORY;
  int k = Y_INVENTORY;

  for (int i = 0; i < MAX_ITEMS; i++) {
    if (items[i] != ID_NULL)
      texture_manager.get_texture(items[i]).render(renderer, NULL, j, k);
    
    // Si el item esta seleccionado lo marcamos
    if(is_selected && (index == i))
      texture_manager.get_texture(ID_SELECTOR).render(renderer, NULL, j, k);

    // Dejamos 2px de espacio horizontal entre items
    j += ITEM_SIZE + ESPACIO_HORIZONTAL;
    // Si ya se renderizaron 4 items se pasa a la siguiente fila
    if (((i + 1) % 4) == 0) {
      j = X_INVENTORY;
      // Dejamos 3px de espacio vertical entre items
      k += ITEM_SIZE + ESPACIO_VERTICAL;
    }
  }
}

