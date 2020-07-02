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
      collided_entity(-1) {}

void Projectile::update() {
  std::cout << "projectile of id: " << unique_id << " x: " << x_position << " y: " << y_position << std::endl;
  if (range == 0) ModelException("Projectile cant move any more!", "11");
  int next_x = x_position + get_next_x();
  int next_y = y_position + get_next_y();
  if (map->can_ocupy_cell(next_x, next_y)) {
    map->ocupy_cell(next_x, next_y, unique_id);
    map->empty_cell(x_position, y_position);
    x_position = next_x;
    y_position = next_y;
    range--;
  }
  else if (map->tile_is_valid(next_x, next_y)) {
    collided_entity = map->get_uid(next_x, next_y);
    collided = true;
    std::cout << "collided with id" << collided_entity << std::endl;
  }
  if (range == 0) {
    alive = false;
  }
}

void Projectile::move() {
  
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
  alive = false;
}

Projectile::~Projectile() {}
