#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "SDL2/SDL.h"
#include "texture_manager.h"
#define MAX_ITEMS 20
#define ITEM_SIZE 32
#define X_INVENTORY 641
#define Y_INVENTORY 170
#define ESPACIO_HORIZONTAL 2
#define ESPACIO_VERTICAL 3

class Inventory {
 private:
  int gold;
  id_texture_t items[MAX_ITEMS];

 public:
  Inventory();
  ~Inventory();
  void add_item(id_texture_t);
  id_texture_t drop_item(int);
  void change_gold(int);
  void render(SDL_Renderer*);
};



#endif