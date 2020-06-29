#include "item.h"

Item::Item() { is_equipped = false; }

Item::Item(id_texture_t id, int new_x, int new_y) {
  x = new_x*TILE_SIZE;
  y = new_y*TILE_SIZE;
  // Estas medidas son de la arma  sin equipar
  width = 32;
  height = 32;
  set_item_dimensions(id);
  animation_equipped = Animation(frame_equipped.w, frame_equipped.h, item_type);
  is_equipped = true;
}

Item::~Item() {}

void Item::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  texture_manager.get_texture(item_type).render(
      renderer, NULL, x - width / 2 - x_rel, y - height / 2 - y_rel);
}

// Posiblemente no haga falta
// Debe recibir del pj el body_rect.x y el body_rect.y + height/2
/*void Item::render_weapon_equipped(SDL_Renderer* renderer, int x_player,
                                  int y_player) {
  texture_manager->get_texture(item_equipped)
      .render(renderer, &frame_equipped, x_player, y_player);
}*/

void Item::get_next_frame(move_t move_type) {
  frame_equipped = animation_equipped.get_next_clip(move_type);
}

void Item::set_item_dimensions(id_texture_t id) {
  size_xs = false;
  switch (id) {
    // Armas
    case ID_SWORD:
      frame_equipped = {0, 0, 25, 48};
      item_equipped = ID_SWORD_EQUIPPED;
      break;

    case ID_AXE:
      frame_equipped = {0, 0, 25, 48};
      item_equipped = ID_AXE_EQUIPPED;
      break;

    case ID_HAMMER:
      frame_equipped = {0, 0, 25, 48};
      item_equipped = ID_HAMMER_EQUIPPED;
      break;

    case ID_ASH_STICK:
      frame_equipped = {0, 0, 25, 48};
      item_equipped = ID_ASH_STICK_EQUIPPED;
      break;

    case ID_KNOTTY_STAFF:
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_KNOTTY_STAFF_EQUIPPED;
      break;

    case ID_CRIMPED_STAFF:
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_CRIMPED_STAFF_EQUIPPED;
      break;

    case ID_SIMPLE_BOW:
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_SIMPLE_BOW_EQUIPPED;
      break;

    case ID_COMPOUND_BOW:
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_COMPOUND_BOW_EQUIPPED;
      break;

    // Escudos
    case ID_IRON_SHIELD:
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_IRON_SHIELD_EQUIPPED;
      break;

    case ID_TURTLE_SHIELD:
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_TURTLE_SHIELD_EQUIPPED;
      break;

    // Cascos y sombreros
    case ID_MAGIC_HAT:
      frame_equipped = {0, 0, 17, 19};
      item_equipped = ID_MAGIC_HAT_EQUIPPED;
      break;

    case ID_HOOD:
      frame_equipped = {0, 0, 17, 18};
      item_equipped = ID_HOOD_EQUIPPED;
      break;

    case ID_IRON_HELMET:
      frame_equipped = {0, 0, 17, 18};
      item_equipped = ID_IRON_HELMET_EQUIPPED;
      break;

    // Armaduras y vestimentas
    case ID_LEATHER_ARMOR:
      // El frame es el mismo para ambas texturas
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_LEATHER_ARMOR_EQUIPPED;
      item_equipped_xs = ID_LEATHER_ARMOR_XS_EQUIPPED;
      size_xs = true;
      break;

    case ID_PLATE_ARMOR:
      // El frame es el mismo para ambas texturas
      frame_equipped = {0, 0, 25, 45};
      item_equipped = ID_PLATE_ARMOR_EQUIPPED;
      item_equipped_xs = ID_PLATE_ARMOR_XS_EQUIPPED;
      size_xs = true;
      break;

    case ID_BLUE_TUNIC:
      frame_equipped = {0, 0, 17, 19};
      item_equipped = ID_BLUE_TUNIC_EQUIPPED;
      break;
  }
}

//bool Item::equiped() { return is_equipped; }

/*
id_texture_t Item::get_texture(id_texture_t type_character) {
  if ((type_character == ID_GNOME || type_character == ID_DWARF) && size_xs) {
    return item_equipped_xs;
  }
  else {
    return item_equipped;
  }
}
*/