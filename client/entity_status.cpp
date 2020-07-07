#include "entity_status.h"

EntityStatus::EntityStatus() {}

EntityStatus::EntityStatus(int type_ent, int new_x, int new_y, int spell)
    : x(new_x), y(new_y) {
  // poner los id que usa el server
  switch (type_ent) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      type_entity = ITEM;
      item = (item_t)type_ent;
      break;

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

    case 37:
      type_entity = ITEM;
      item = GOLD;
      break;
  }
  // Vemos si la entidad la esta afectando alguna magia/estado
  switch (spell) {
    case 0:
      spellbound = ID_NULL;
      lifetime = 0;
      break;

    case 1:
      spellbound = ID_BLEEDING;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_BLEEDING;
      break;

    case 2:
      spellbound = ID_MAGIC_ARROW;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_MAGIC_ARROW;
      break;

    case 3:
      spellbound = ID_HEAL;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_HEAL;
      break;

    case 4:
      spellbound = ID_ELECTRIC_SHOCK;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_ELECTRIC_SHOCK;
      break;

    case 5:
      spellbound = ID_EXPLOSION;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_EXPLOSION;
      break;
  }
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
}

bool EntityStatus::is_equal(EntityStatus other_status) {
  return (type_entity == other_status.type_entity && x == other_status.x &&
          y == other_status.y && is_alive == other_status.is_alive);
}

entity_t EntityStatus::get_type_entity() const { return type_entity; }

int EntityStatus::get_x() const { return x; }

int EntityStatus::get_y() const { return y; }

id_texture_t EntityStatus::is_afected() const { return spellbound; }

int EntityStatus::get_life_time() const { return lifetime; }

item_t EntityStatus::get_item() const { return item; }