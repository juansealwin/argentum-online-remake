#include "inventory.h"

Inventory::Inventory() {
  for (int i = 0; i < MAX_ITEMS_INVENTORY; i++) {
    items[i].first = ID_NULL;
    items[i].second = false;
  }
}

Inventory::~Inventory() {}

void Inventory::add_item(id_texture_t new_item, bool equipped) {
  int i = 0;
  while ((items[i].first != ID_NULL)) {
    i++;
  }
  items[i].first = new_item;
  items[i].second = equipped;
}

void Inventory::render(SDL_Renderer* renderer) {
  int j = X_SHOP * texture_manager.get_w_ratio();
  int k = Y_SHOP * texture_manager.get_h_ratio();
  int items_per_row = 4;

  if (texture_manager.get_w_ratio() > RATIO_800) items_per_row++;

  for (int i = 0; i < MAX_ITEMS_SHOP; i++) {
    if (items[i].first != ID_NULL)
      texture_manager.get_texture(items[i].first).render(renderer, NULL, j, k);

    // Dejamos 2px de espacio horizontal entre items
    j += ITEM_SIZE + X_PADDING;
    // Si ya se renderizaron 4 items se pasa a la siguiente fila
    if (((i + 1) % items_per_row) == 0) {
      j = X_SHOP * texture_manager.get_w_ratio();
      // Dejamos 3px de espacio vertical entre items
      k += ITEM_SIZE + Y_PADDING;
    }
  }
}

void Inventory::render(SDL_Renderer* renderer, bool is_selected, int index) {
  int j = X_INVENTORY * texture_manager.get_w_ratio();
  int k = Y_INVENTORY * texture_manager.get_h_ratio();
  int items_per_row = 4;

  if (texture_manager.get_w_ratio() > RATIO_800) items_per_row++;

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
    if (((i + 1) % items_per_row) == 0) {
      j = X_INVENTORY * texture_manager.get_w_ratio();
      // Dejamos 3px de espacio vertical entre items
      k += ITEM_SIZE + Y_PADDING;
    }
  }
}

std::map<int, std::pair<id_texture_t, bool>> Inventory::get_items() {
  return items;
}