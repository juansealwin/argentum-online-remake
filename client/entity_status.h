#ifndef ENTITY_STATUS_H
#define ENTITY_STATUS_H

#include "character.h"
#include "inventory.h"
#include "types.h"

class EntityStatus {
 private:
  entity_t type_entity;
  int x;
  int y;
  bool is_alive;
  id_texture_t spellbound;
  item_t item;
  int lifetime;


 public:
  EntityStatus();
  EntityStatus(int, int, int, int);
  ~EntityStatus();
  EntityStatus& operator=(const EntityStatus&);
  bool is_equal(EntityStatus);
  int get_x() const;
  int get_y() const;
  entity_t get_type_entity() const;
  id_texture_t is_afected() const;
  int get_life_time() const;
  item_t get_item() const;
};

#endif
