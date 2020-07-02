#include "projectile.h"

#include <iostream>
Projectile::Projectile(unsigned int unique_id, int x, int y, int type,
                       char repr, const unsigned int damage,
                       const bool critical, const unsigned int attacker_id,
                       const unsigned int range,
                       const orientation_t orientation, Map *map)
    : Entity(unique_id, x, y, type, repr),
      damage(damage),
      critical(critical),
      attacker_id(attacker_id),
      range(range),
      orientation(orientation),
      map(map),
      collided(false),
      collided_entity(-1) {
        impact_at_position(x,y);
      }

void Projectile::update() {
  if (collided) return;
  if (range == 0) ModelException("Projectile cant move any more!", "11");
  int next_x = x_position + get_next_x();
  int next_y = y_position + get_next_y();
  impact_at_position(next_x, next_y);
  // std::cout << "trying ocupy cell..." << std::endl;
  // if (map->can_ocupy_cell(next_x, next_y)) {
  //   std::cout << "can ocupy cell..." << std::endl;
  //   std::cout << "Calling ocupy cell" << std::endl;
  //   map->ocupy_cell(next_x, next_y, unique_id);
  //   std::cout << "Calling empty cell" << std::endl;
  //   map->empty_cell(x_position, y_position);
  //   x_position = next_x;
  //   y_position = next_y;
  //   range--;
  //   std::cout << "out of update fun" << std::endl;
  // }
  // else if (map->tile_is_valid(next_x, next_y)) {
  //   std::cout << "cell is valid..." << std::endl;
  //   collided_entity = map->get_uid(next_x, next_y);
  //   collided = true;
  //   std::cout << "collided with id" << collided_entity << std::endl;
  // }
  if (range == 0) {
    alive = false;
  }
}

void Projectile::impact_at_position(int x, int y) {
if (map->can_ocupy_cell(x, y)) {
    map->ocupy_cell(x, y, unique_id);
    map->empty_cell(x_position, y_position);
    x_position = x;
    y_position = y;
    range--;
  }
  else if (map->tile_is_valid(x, y)) {
    collided_entity = map->get_uid(x, y);
    collided = true;
    std::cout << "collided with id" << collided_entity << std::endl;
  }
}

int Projectile::get_collided_entity() {
  return collided_entity;
}

int Projectile::get_next_x() {
  switch (orientation) {
    case (orientation_down):
      return 1;
    case (orientation_up):
      return -1;
    default:
      return 0;
  }
}

int Projectile::get_next_y() {
  switch (orientation) {
    case (orientation_left):
      return -1;
    case (orientation_right):
      return 1;
    default:
      return 0;
  }
}

unsigned int Projectile::get_damage() {
  return damage;
}
bool Projectile::is_critical() {
  return critical;
}

unsigned int Projectile::get_attacker_id() {
  return attacker_id;
}

void Projectile::kill() {
  std::cout << "killing projectile" << std::endl;
  map->empty_cell(x_position, y_position);
  alive = false;
}

Projectile::~Projectile() {}
