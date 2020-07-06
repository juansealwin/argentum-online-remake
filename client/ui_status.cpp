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

void UIStatus::add_item(int new_item, int slot) {
  inventory.add_item(get_item(new_item), slot);
}

void UIStatus::add_item(int new_item) {
  inventory.add_item(get_item(new_item));
}

void UIStatus::render(SDL_Renderer* renderer, bool is_selected, int index) {
  texture_manager.get_texture(ID_UI).render(renderer, NULL, 0, 0);
  inventory.render(renderer, is_selected, index);
}

id_texture_t UIStatus::get_item(int new_item) {
  id_texture_t item;
  
  switch ((item_t)new_item) {
    case DUMMY_ITEM:
      item = ID_NULL;
      break;

    case TURTLE_SHIELD:
      item = ID_TURTLE_SHIELD;
      break;

    case IRON_SHIELD:
      item = ID_IRON_SHIELD;
      break;

    case HOOD:
      item = ID_HOOD;
      break;

    case IRON_HELMET:
      item = ID_IRON_HELMET;
      break;

    case MAGIC_HAT:
      item = ID_MAGIC_HAT;
      break;

    case LEATHER_ARMOR:
      item = ID_LEATHER_ARMOR;
      break;

    case PLATE_ARMOR:
      item = ID_PLATE_ARMOR;
      break;

    case BLUE_TUNIC:
      item = ID_BLUE_TUNIC;
      break;

    case HP_POTION:
      item = ID_HP_POTION;
      break;

    case MANA_POTION:
      item = ID_MANA_POTION;
      break;

    case SWORD:
      item = ID_SWORD;
      break;

    case AXE:
      item = ID_AXE;
      break;

    case HAMMER:
      item = ID_HAMMER;
      break;

    case SIMPLE_BOW:
      item = ID_SIMPLE_BOW;
      break;

    case COMPUND_BOW:
      item = ID_COMPOUND_BOW;
      break;

    case ASH_STICK:
      item = ID_ASH_STICK;
      break;

    case GNARLED_STAFF:
      item = ID_KNOTTY_STAFF;
      break;

    case CRIMP_STAFF:
      item = ID_CRIMPED_STAFF;
      break;

    case ELVEN_FLUTE:
      item = ID_ELVEN_ELUDE;
      break;

    case GOLD:
      item = ID_GOLD;
  }
  return item;
}

std::map<int, std::pair<id_texture_t, bool>> UIStatus::get_items() {
  return inventory.get_items();
}