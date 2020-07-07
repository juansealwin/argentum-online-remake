#ifndef UI_STATUS_H
#define UI_STARUS_H

#include "inventory.h"
#include "types.h"

class UIStatus {
 private:
  Inventory inventory;
  std::string hero_name;
  int max_health;
  int health;
  int max_mana;
  int mana;
  int level;
  int xp_limit;
  int current_xp;
  id_texture_t get_item(int);

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