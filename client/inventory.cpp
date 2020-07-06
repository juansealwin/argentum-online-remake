#include "inventory.h"

Inventory::Inventory() {
  for (int i = 0; i < MAX_ITEMS; i++) {
    items[i].first = ID_NULL;
    items[i].second = false;
  }
  gold = 0;
}

Inventory::Inventory(int new_gold) {
  for (int i = 0; i < MAX_ITEMS; i++) {
    items[i].first = ID_NULL;
    items[i].second = false;
  }
  gold = new_gold;
}

Inventory::~Inventory() {}

Inventory& Inventory::operator=(const Inventory& other_inv) {
  gold = other_inv.gold;

  std::map<int, std::pair<id_texture_t, bool>>::const_iterator it;

  for (it = other_inv.items.begin(); it != other_inv.items.end(); it++) {
    if (it->second.first == ID_NULL) {
      items[it->first].first = ID_NULL;
      items[it->first].second = false;
    } else if (it->second.second) {
      add_item(it->second.first, it->first);
    } else {
      add_item(it->second.first);
    }
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

void Inventory::change_gold(int income) { gold = income; }

void Inventory::render(SDL_Renderer* renderer, bool is_selected, int index) {
  int j = X_INVENTORY;
  int k = Y_INVENTORY;

  for (int i = 0; i < MAX_ITEMS; i++) {
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
    j += ITEM_SIZE + ESPACIO_HORIZONTAL;
    // Si ya se renderizaron 4 items se pasa a la siguiente fila
    if (((i + 1) % 4) == 0) {
      j = X_INVENTORY;
      // Dejamos 3px de espacio vertical entre items
      k += ITEM_SIZE + ESPACIO_VERTICAL;
    }
  }
}


std::map<int, std::pair<id_texture_t, bool>> Inventory::get_items(){
  return items;
}