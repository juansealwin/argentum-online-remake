#ifndef ENTITY_STATUS_H
#define ENTITY_STATUS_H

#include "character.h"
#include "inventory.h"
#include "types.h"

class EntityStatus {
 private:
  entity_t type_entity;
  id_texture_t item;
  int x;
  int y;
  move_t orientation;
  bool is_alive;
  id_texture_t spellbound;
  int lifetime;
  bool meditating;
  id_texture_t helmet;
  id_texture_t armor;
  id_texture_t shield;
  id_texture_t weapon;

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
  EntityStatus& operator=(const EntityStatus&);
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
