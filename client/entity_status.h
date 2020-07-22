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
  id_texture_t item = ID_NULL;
  move_t orientation = MOVE_DOWN;
  bool is_alive = true;
  id_texture_t spellbound = ID_NULL;
  int lifetime = 0;
  bool meditating = false;
  id_texture_t helmet = ID_NULL;
  id_texture_t armor = ID_NULL;
  id_texture_t shield = ID_NULL;
  id_texture_t weapon = ID_NULL;

 public:
  EntityStatus();
  // Constructor para drops
  EntityStatus(id_texture_t, int, int);
  // Constructor para npcs no atacables
  EntityStatus(int, int, int);
  // Constructor para npcs atacables
  EntityStatus(int, int, int, int, int);
  // Constructor para personajes jugables
  EntityStatus(int, int, int, int, int, int, int, id_texture_t, id_texture_t,
               id_texture_t, id_texture_t);
  ~EntityStatus();
  bool is_equal(EntityStatus);
  int get_x() const;
  int get_y() const;
  entity_t get_type_entity() const;
  id_texture_t is_afected() const;
  int get_life_time() const;
  id_texture_t get_item() const;
  bool is_ghost() const;
  void set_spellbound(int);
  bool is_meditating() const;
  id_texture_t get_equipped(equipped_t);
  move_t get_orientation() const;
  sound_t get_cast_sound();
};

#endif
