#include "inventory.h"

Inventory::Inventory() {
  for (int i = 0; i < MAX_ITEMS_INVENTORY; i++) {
    items[i].first = ID_NULL;
    items[i].second = false;
  }
}

Inventory::~Inventory() {}

Inventory& Inventory::operator=(const Inventory& other_inv) {
  std::map<int, std::pair<id_texture_t, bool>>::const_iterator it;

  for (it = other_inv.items.begin(); it != other_inv.items.end(); it++) {
    items[it->first].first = it->second.first;
    items[it->first].second = it->second.second;
  }
  return *this;
}

void Inventory::add_item(id_texture_t new_item) {
  int i = 0;
  while ((items[i].first != ID_NULL)) {
    i++;
  }
  items[i].first = new_item;
  items[i].second = false;
}

void Inventory::add_item(id_texture_t new_item, int i) {
  items[i].first = new_item;
  items[i].second = true;
}

id_texture_t Inventory::drop_item(int index) {
  id_texture_t temp = ID_NULL;

  if (items[index].first != ID_NULL) {
    temp = items[index].first;
    items[index].first = ID_NULL;
    if (items[index].second) items[index].second = false;
  }
  return temp;
}

void Inventory::render(SDL_Renderer* renderer) {
  int j = X_SHOP;
  int k = Y_SHOP;

  for (int i = 0; i < MAX_ITEMS_SHOP; i++) {
    if (items[i].first != ID_NULL)
      texture_manager.get_texture(items[i].first).render(renderer, NULL, j, k);

    // Dejamos 2px de espacio horizontal entre items
    j += ITEM_SIZE + X_PADDING;
    // Si ya se renderizaron 4 items se pasa a la siguiente fila
    if (((i + 1) % 4) == 0) {
      j = X_INVENTORY;
      // Dejamos 3px de espacio vertical entre items
      k += ITEM_SIZE + Y_PADDING;
    }
  }
}

void Inventory::render(SDL_Renderer* renderer, bool is_selected, int index) {
  int j = X_INVENTORY;
  int k = Y_INVENTORY;

  for (int i = 0; i < MAX_ITEMS_INVENTORY; i++) {
    if (items[i].first != ID_NULL)
      texture_manager.get_texture(items[i].first).render(renderer, NULL, j, k);

    // Si el item esta equipado lo marcamos
    if (items[i].second)
      texture_manager.get_texture(ID_ITEM_EQUIPPED)
          .render(renderer, NULL, j, k);

    // Si el item esta seleccionado lo marcamos
    if (is_selected && (index == i))
      texture_manager.get_texture(ID_SELECTOR).render(renderer, NULL, j, k);

    // Dejamos 2px de espacio horizontal entre items
    j += ITEM_SIZE + X_PADDING;
    // Si ya se renderizaron 4 items se pasa a la siguiente fila
    if (((i + 1) % 4) == 0) {
      j = X_INVENTORY;
      // Dejamos 3px de espacio vertical entre items
      k += ITEM_SIZE + Y_PADDING;
    }
  }
}

std::map<int, std::pair<id_texture_t, bool>> Inventory::get_items() {
  return items;
}