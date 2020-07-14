#ifndef UI_STATUS_H
#define UI_STARUS_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "inventory.h"
#include "text_box.h"
#include "types.h"

class UIStatus {
 private:
  Inventory inventory;
  Inventory bank;
  Inventory market;
  std::map<text_box_t, std::string> text_messages;
  bool second_inventory;
  inventory_t bank_or_market;

 public:
  UIStatus();
  ~UIStatus();
  UIStatus& operator=(const UIStatus&);
  // seteo de msj de ui: name, lvl, mx_hp, hp, max_mana, mana, goal_xp, xp, gold
  void set_ui_messages(std::string, int, int, int, int, int, int, int, int);
  void render(SDL_Renderer*, std::string, bool, int);
  void add_item(inventory_t, id_texture_t);
  void add_item(inventory_t, id_texture_t, int);
  void close_shops();
  void charge_messages(std::string, std::string, std::string, std::string);
  std::map<int, std::pair<id_texture_t, bool>> get_items();
};

#endif