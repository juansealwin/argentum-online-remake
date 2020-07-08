#include "ui_status.h"

UIStatus::UIStatus()
    : hero_name(""),
      level(0),
      max_health(0),
      health(0),
      max_mana(0),
      mana(0),
      xp_limit(0),
      current_xp(0) {
  inventory = Inventory(0);
}

UIStatus::UIStatus(std::string name, int lvl, int max_hp, int hp, int max_mn,
                   int mn, int goal_xp, int xp, int gold)
    : hero_name(name),
      level(lvl),
      max_health(hp),
      health(hp),
      max_mana(max_mn),
      mana(mn),
      xp_limit(goal_xp),
      current_xp(xp) {
  // Vaciamos el inventario anterior
  inventory = Inventory(gold);
}

UIStatus::~UIStatus() {}

UIStatus& UIStatus::operator=(const UIStatus& other_status) {
  hero_name = other_status.hero_name;
  level = other_status.level;
  max_health = other_status.max_health;
  health = other_status.health;
  max_mana = other_status.max_mana;
  mana = other_status.mana;
  xp_limit = other_status.xp_limit;
  current_xp = other_status.current_xp;
  inventory = other_status.inventory;
  return *this;
}

void UIStatus::add_item(id_texture_t new_item, int slot) {
  inventory.add_item(new_item, slot);
}

void UIStatus::add_item(id_texture_t new_item) {
  inventory.add_item(new_item);
}

void UIStatus::render(SDL_Renderer* renderer, bool is_selected, int index) {
  texture_manager.get_texture(ID_UI).render(renderer, NULL, 0, 0);
  inventory.render(renderer, is_selected, index);
}

std::map<int, std::pair<id_texture_t, bool>> UIStatus::get_items() {
  return inventory.get_items();
}