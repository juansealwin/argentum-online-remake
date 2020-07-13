#include "entity_status.h"

EntityStatus::EntityStatus() {}

EntityStatus::EntityStatus(id_texture_t texture_item, int new_x, int new_y)
    : item(texture_item), x(new_x), y(new_y) {
  type_entity = ITEM;
  spellbound = ID_NULL;
}

EntityStatus::EntityStatus(int type_ent, int new_x, int new_y)
    : x(new_x), y(new_y) {
  // poner los id que usa el server
  switch (type_ent) {
    case 33:
      type_entity = PRIEST;
      break;

    case 34:
      type_entity = MERCHANT;
      break;

    case 35:
      type_entity = BANKER;
      break;
  }
  set_spellbound(DUMMY_ITEM);
  helmet = ID_NULL;
  armor = ID_NULL;
  shield = ID_NULL;
  weapon = ID_NULL;
}

EntityStatus::EntityStatus(int type_ent, int new_x, int new_y, int affected_by)
    : x(new_x), y(new_y) {
  // poner los id que usa el server
  switch (type_ent) {
    case 29:
      type_entity = GOBLIN;
      break;

    case 30:
      type_entity = SPIDER;
      break;

    case 31:
      type_entity = SKELETON;
      break;

    case 32:
      type_entity = ZOMBIE;
      break;

    case 33:
      type_entity = PRIEST;
      break;

    case 34:
      type_entity = MERCHANT;
      break;

    case 35:
      type_entity = BANKER;
      break;
  }
  set_spellbound(affected_by);
  helmet = ID_NULL;
  armor = ID_NULL;
  shield = ID_NULL;
  weapon = ID_NULL;
}

EntityStatus::EntityStatus(int type_ent, int new_x, int new_y, int ghost_mod,
                           int affected_by, id_texture_t new_helmet,
                           id_texture_t new_armor, id_texture_t new_shield,
                           id_texture_t new_weapon)
    : x(new_x),
      y(new_y),
      is_alive(ghost_mod),
      helmet(new_helmet),
      armor(new_armor),
      shield(new_shield),
      weapon(new_weapon) {
  switch (type_ent) {
    case 25:
      type_entity = HUMAN;
      break;

    case 26:
      type_entity = ELF;
      break;

    case 27:
      type_entity = DWARF;
      break;

    case 28:
      type_entity = GNOME;
      break;
  }
  set_spellbound(affected_by);
}

EntityStatus::~EntityStatus() {}

EntityStatus& EntityStatus::operator=(const EntityStatus& other_status) {
  type_entity = other_status.type_entity;
  x = other_status.x;
  y = other_status.y;
  is_alive = other_status.is_alive;
  spellbound = other_status.spellbound;
  item = other_status.item;
  lifetime = other_status.lifetime;
  helmet = other_status.helmet;
  armor = other_status.armor;
  shield = other_status.shield;
  weapon = other_status.weapon;
}

void EntityStatus::set_spellbound(int affected_by) {
  // Vemos si la entidad la esta afectando alguna magia/estado
  // Corresponde al numero de item_t que le haya atinado
  switch ((item_t)affected_by) {
    case DUMMY_ITEM:
      spellbound = ID_NULL;
      lifetime = 0;
      break;

    case SWORD:
    case AXE:
    case HAMMER:
    case SIMPLE_BOW:
    case COMPOUND_BOW:
      spellbound = ID_BLEEDING;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_BLEEDING;
      break;

    case ASH_STICK:
      spellbound = ID_MAGIC_ARROW;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_MAGIC_ARROW;
      break;

    case GNARLED_STAFF:
      spellbound = ID_ELECTRIC_SHOCK;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_ELECTRIC_SHOCK;
      break;

    case CRIMP_STAFF:
      spellbound = ID_EXPLOSION;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_EXPLOSION;
      break;

    case ELVEN_FLUTE:
      spellbound = ID_HEAL;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_HEAL;
      break;
  }
}

bool EntityStatus::is_equal(EntityStatus other_status) {
  return (type_entity == other_status.type_entity && x == other_status.x &&
          y == other_status.y && is_alive == other_status.is_alive &&
          helmet == other_status.helmet && armor == other_status.armor &&
          shield == other_status.shield && weapon == other_status.weapon);
}

entity_t EntityStatus::get_type_entity() const { return type_entity; }

int EntityStatus::get_x() const { return x; }

int EntityStatus::get_y() const { return y; }

id_texture_t EntityStatus::is_afected() const { return spellbound; }

int EntityStatus::get_life_time() const { return lifetime; }

bool EntityStatus::is_ghost() const { return is_alive; }

id_texture_t EntityStatus::get_item() const { return item; }

id_texture_t EntityStatus::get_equipped(equipped_t type_item) {
  if (type_item == HELMET)
    return helmet;
  else if (type_item == ARMOR)
    return armor;
  else if (type_item == SHIELD)
    return shield;
  else if (type_item == WEAPON)
    return weapon;
}