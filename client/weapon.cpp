#include "weapon.h"

Weapon::Weapon(id_texture_t id, int new_x, int new_y) {
  x = new_x;
  y = new_y;
  set_weapon_dimensions(id);
  animation_equipped =
      Animation(frame_equipped.w, frame_equipped.h, weapon_type);
}

Weapon::~Weapon() {}

void Weapon::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  texture_manager->get_texture(weapon_type)
      .render(renderer, NULL, x - width / 2 - x_rel, y - height / 2 - y_rel);
}

// Debe recibir del pj el body_rect.x y el body_rect.y + height/2
void Weapon::render_equiped(SDL_Renderer* renderer, int x_player,
                            int y_player) {
  texture_manager->get_texture(weapon_equipped)
      .render(renderer, &frame_equipped, x_player, y_player);
}

void Weapon::get_next_frame(move_t move_type) {
  frame_equipped = animation_equipped.get_next_clip(move_type);
}

void Weapon::set_weapon_dimensions(id_texture_t id) {
  switch (id) {
    case ID_SWORD:
      // Estas medidas son de la arma  sin equipar
      width = 32;
      height = 32;
      frame_equipped = {0, 0, 25, 48};
      weapon_equipped = ID_SWORD_EQUIPPED;
      break;

    case ID_AXE:
      // Estas medidas son de la arma  sin equipar
      width = 32;
      height = 32;
      frame_equipped = {0, 0, 25, 48};
      weapon_equipped = ID_AXE_EQUIPPED;
      break;

    case ID_HAMMER:
      // Estas medidas son de la arma  sin equipar
      width = 32;
      height = 32;
      frame_equipped = {0, 0, 25, 48};
      weapon_equipped = ID_HAMMER_EQUIPPED;
      break;

    case ID_ASH_STICK:
      // Estas medidas son de la arma  sin equipar
      width = 32;
      height = 32;
      frame_equipped = {0, 0, 25, 48};
      weapon_equipped = ID_ASH_STICK_EQUIPPED;
      break;

    case ID_KNOTTY_STAFF:
      // Estas medidas son de la arma  sin equipar
      width = 32;
      height = 32;
      frame_equipped = {0, 0, 25, 45};
      weapon_equipped = ID_KNOTTY_STAFF_EQUIPPED;
      break;

    case ID_CRIMPED_STAFF:
      // Estas medidas son de la arma  sin equipar
      width = 32;
      height = 32;
      frame_equipped = {0, 0, 25, 45};
      weapon_equipped = ID_CRIMPED_STAFF_EQUIPPED;
      break;
  }
}