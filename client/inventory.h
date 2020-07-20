#ifndef INVENTORY_H
#define INVENTORY_H

#include "SDL2/SDL.h"
#include "texture_manager.h"
#include "types.h"
#include <map>
#define MAX_ITEMS_INVENTORY 20
#define MAX_ITEMS_SHOP 16
#define ITEM_SIZE 32
#define X_INVENTORY 641
#define Y_INVENTORY 170
#define X_SHOP 641
#define Y_SHOP 453
#define X_PADDING 2
#define Y_PADDING 3
#define RATIO_800 1 

class Inventory {
 private:
  std::map<int, std::pair<id_texture_t, bool>> items;
  bool is_selected = false;
  int item_selected;

 public:
  Inventory();
  ~Inventory();
  Inventory& operator=(const Inventory&);
  // Agrega items al inventario/banco/mercado
  void add_item(id_texture_t, bool);
  // agrega items mercado o banco
  //void add_item(id_texture_t, int);
  id_texture_t drop_item(int);
  void change_gold(int);
  // Render para el inventario
  void render(SDL_Renderer*, bool, int);
  // Render para el banco/mercado
  void render(SDL_Renderer*);
  std::map<int, std::pair<id_texture_t, bool>> get_items();
};

#endif