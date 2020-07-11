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
  std::map<text_box_t, std::string> text_messages;
  /*TextBox level(LEVEL, text_messages[LEVEL]);
  TextBox name(NAME, text_messages[NAME]);
  TextBox exp(EXP, text_messages[EXP]);
  TextBox gold(GOLD_QUANTITY, text_messages[GOLD_QUANTITY]);
  TextBox health(HEALTH, text_messages[HEALTH]);
  TextBox mana(MANA, text_messages[MANA]);*/

 public:
  UIStatus();
  // Constructor: name, lvl, mx_hp, hp, max_mana, mana, goal_xp, xp, gold
  UIStatus(std::string, int, int, int, int, int, int, int, int);
  ~UIStatus();
  UIStatus& operator=(const UIStatus&);
  void render(SDL_Renderer*, bool, int);
  void add_item(id_texture_t);
  void add_item(id_texture_t, int);
  std::map<int, std::pair<id_texture_t, bool>> get_items();
};

#endif