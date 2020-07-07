#include "playable_character.h"

PlayableCharacter::PlayableCharacter(entity_t id_char, int new_x, int new_y,
                                     id_texture_t new_helmet,
                                     id_texture_t new_armor,
                                     id_texture_t new_shield,
                                     id_texture_t new_weapon) {
  x = new_x * TILE_SIZE;
  y = new_y * TILE_SIZE;
  set_character_features(id_char);
  set_head_dimensions(id_char);
  animation_move = Animation(width, height, type_character);
  set_item_dimensions(new_helmet);
  set_item_dimensions(new_armor);
  set_item_dimensions(new_weapon);
  set_item_dimensions(new_shield);
}

PlayableCharacter::PlayableCharacter(const PlayableCharacter& other_pc) {
  /** Copiamos la parte de Drawable **/
  x = other_pc.x;
  y = other_pc.y;
  // Colocamos las dimensiones del personaje
  width = other_pc.width;
  height = other_pc.height;

  /** Copiamos la parte de Character **/
  type_character = other_pc.type_character;
  animation_move = other_pc.animation_move;
  body_rect = other_pc.body_rect;
  walk = other_pc.walk;
  spellbound = other_pc.spellbound;

  /** Copiamos la parte de PlayableCharacter **/
  // Colocamos las dimensiones de su cabeza
  type_head = other_pc.type_head;
  head_rect = other_pc.head_rect;
  helmet = other_pc.helmet;
  armor = other_pc.armor;
  shield = other_pc.shield;
  weapon = other_pc.weapon;
}

PlayableCharacter& PlayableCharacter::operator=(
    const PlayableCharacter& other_pc) {
  /** Copiamos la parte de Drawable **/
  x = other_pc.x;
  y = other_pc.y;
  // Colocamos las dimensiones del personaje
  width = other_pc.width;
  height = other_pc.height;

  /** Copiamos la parte de Character **/
  type_character = other_pc.type_character;
  animation_move = other_pc.animation_move;
  body_rect = other_pc.body_rect;
  walk = other_pc.walk;
  spellbound = other_pc.spellbound;

  /** Copiamos la parte de PlayableCharacter **/
  // Colocamos las dimensiones de su cabeza
  type_head = other_pc.type_head;
  head_rect = other_pc.head_rect;
  helmet = other_pc.helmet;
  armor = other_pc.armor;
  shield = other_pc.shield;
  weapon = other_pc.weapon;
  return *this;
}

PlayableCharacter::~PlayableCharacter() {}

// A los jugables hay que actualizarles el perfil
void PlayableCharacter::move(move_t move_type) {
  body_rect = animation_move.get_next_clip(move_type);
  update_face_profile(move_type);
}

void PlayableCharacter::update_face_profile(move_t move_type) {
  head_rect.x = move_type * head_rect.w;
}

void PlayableCharacter::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  // Solo se renderiza la armadura o el cuerpo para no repetir manos y pies
  if (armor) {
    texture_manager.get_texture(armor).render(renderer, &body_rect, x - x_rel,
                                              y - height / 2 - y_rel);
  } else {
    texture_manager.get_texture(type_character)
        .render(renderer, &body_rect, x - x_rel, y - height / 2 - y_rel);
  }
  // Renderizamos cabeza
  texture_manager.get_texture(type_head).render(
      renderer, &head_rect, x + head_rect.w / 4 - x_rel,
      y - height / 2 - head_rect.h / 2 - y_rel);

  // Si tiene el casco equipado lo renderizamos
  if (helmet) {
    texture_manager.get_texture(helmet).render(
        renderer, &head_rect, x + head_rect.w / 4 - x_rel,
        y - height / 2 - head_rect.h / 2 - y_rel);
  }

  // Si tiene el arma equipada la renderizamos
  if (weapon) {
    texture_manager.get_texture(weapon).render(
        renderer, &body_rect, x - width / 2 - x_rel, y - height / 2 - y_rel);
  }

  // Si esta afectado por algún hechizo lo renderizamos
  if (spellbound.spell_alive())
    spellbound.render(renderer, x - x_rel, y - height / 2 - y_rel);
}

int PlayableCharacter::set_head_dimensions(entity_t id) {
  switch (id) {
    case HUMAN:
      head_rect = {0, 0, 17, 16};
      type_head = ID_HUMAN_HEAD;
      break;

    case ELF:
      head_rect = {0, 0, 17, 16};
      type_head = ID_ELF_HEAD;
      break;

    case GNOME:
      head_rect = {0, 0, 17, 17};
      type_head = ID_GNOME_HEAD;
      break;

    case DWARF:
      head_rect = {0, 0, 17, 17};
      type_head = ID_DWARF_HEAD;
      break;
  }
}

void PlayableCharacter::unequip_item(equipped_t item) {
  // Reinicializamos el item para que no tenga valores dentro
  switch (item) {
    case HELMET:
      helmet = ID_NULL;
      break;

    case ARMOR:
      armor = ID_NULL;
      break;

    case SHIELD:
      shield = ID_NULL;
      break;

    case WEAPON:
      weapon = ID_NULL;
      break;
  }
}

void PlayableCharacter::equip_item(equipped_t item, id_texture_t id) {
  // Reinicializamos el item para que no tenga valores dentro
  switch (item) {
    case HELMET:
      helmet = id;
      break;

    case ARMOR:
      armor = id;
      break;

    case SHIELD:
      shield = id;
      break;

    case WEAPON:
      weapon = id;
      break;
  }
}

void PlayableCharacter::update_equipment(id_texture_t new_helmet,
                                         id_texture_t new_armor,
                                         id_texture_t new_shield,
                                         id_texture_t new_weapon) {
  if (new_helmet == ID_NULL && helmet != ID_NULL)
    unequip_item(HELMET);
  else if (new_helmet != ID_NULL && helmet == ID_NULL)
    equip_item(HELMET, new_helmet);
  if (new_armor == ID_NULL && armor != ID_NULL)
    unequip_item(ARMOR);
  else if (new_armor != ID_NULL && armor == ID_NULL)
    equip_item(ARMOR, new_armor);
  if (new_shield == ID_NULL && shield != ID_NULL)
    unequip_item(SHIELD);
  else if (new_shield != ID_NULL && shield == ID_NULL)
    equip_item(SHIELD, new_shield);
  if (new_weapon == ID_NULL && weapon != ID_NULL)
    unequip_item(WEAPON);
  else if (new_weapon != ID_NULL && weapon == ID_NULL)
    equip_item(WEAPON, new_weapon);
}

/*void PlayableCharacter::get_next_frame(move_t move_type) {
  frame_equipped = animation_equipped.get_next_clip(move_type);
}*/

void PlayableCharacter::set_item_dimensions(id_texture_t id) {
  switch (id) {
    // Armas
    case ID_SWORD:
      // frame_equipped = {0, 0, 25, 48};
      weapon = ID_SWORD_EQUIPPED;
      break;

    case ID_AXE:
      // frame_equipped = {0, 0, 25, 48};
      weapon = ID_AXE_EQUIPPED;
      break;

    case ID_HAMMER:
      // frame_equipped = {0, 0, 25, 48};
      weapon = ID_HAMMER_EQUIPPED;
      break;

    case ID_ASH_STICK:
      // frame_equipped = {0, 0, 25, 48};
      weapon = ID_ASH_STICK_EQUIPPED;
      break;

    case ID_KNOTTY_STAFF:
      // frame_equipped = {0, 0, 25, 45};
      weapon = ID_KNOTTY_STAFF_EQUIPPED;
      break;

    case ID_CRIMPED_STAFF:
      // frame_equipped = {0, 0, 25, 45};
      // item_equipped = ID_CRIMPED_STAFF_EQUIPPED;
      weapon = ID_CRIMPED_STAFF_EQUIPPED;
      break;

    case ID_SIMPLE_BOW:
      // frame_equipped = {0, 0, 25, 45};
      weapon = ID_SIMPLE_BOW_EQUIPPED;
      break;

    case ID_COMPOUND_BOW:
      // frame_equipped = {0, 0, 25, 45};
      weapon = ID_COMPOUND_BOW_EQUIPPED;
      break;

    // Escudos
    case ID_IRON_SHIELD:
      // frame_equipped = {0, 0, 25, 45};
      shield = ID_IRON_SHIELD_EQUIPPED;
      break;

    case ID_TURTLE_SHIELD:
      // frame_equipped = {0, 0, 25, 45};
      shield = ID_TURTLE_SHIELD_EQUIPPED;
      break;

    // Cascos y sombreros
    case ID_MAGIC_HAT:
      // frame_equipped = {0, 0, 17, 19};
      helmet = ID_MAGIC_HAT_EQUIPPED;
      break;

    case ID_HOOD:
      // frame_equipped = {0, 0, 17, 18};
      helmet = ID_HOOD_EQUIPPED;
      break;

    case ID_IRON_HELMET:
      // frame_equipped = {0, 0, 17, 18};
      helmet = ID_IRON_HELMET_EQUIPPED;
      break;

    // Armaduras y vestimentas
    case ID_LEATHER_ARMOR:
      // El frame es el mismo para ambas texturas
      // frame_equipped = {0, 0, 25, 45};
      if (type_character == ID_GNOME || type_character == ID_DWARF)
        armor = ID_LEATHER_ARMOR_XS_EQUIPPED;
      else
        armor = ID_LEATHER_ARMOR_EQUIPPED;
      break;

    case ID_PLATE_ARMOR:
      // El frame es el mismo para ambas texturas
      // frame_equipped = {0, 0, 25, 45};
      if (type_character == ID_GNOME || type_character == ID_DWARF)
        armor = ID_PLATE_ARMOR_EQUIPPED;
      else
        armor = ID_PLATE_ARMOR_XS_EQUIPPED;
      break;

    case ID_BLUE_TUNIC:
      // frame_equipped = {0, 0, 17, 19};
      armor = ID_BLUE_TUNIC_EQUIPPED;
      break;
  }
}

int PlayableCharacter::get_head_w() const { return head_rect.w; }

int PlayableCharacter::get_head_h() const { return head_rect.h; }