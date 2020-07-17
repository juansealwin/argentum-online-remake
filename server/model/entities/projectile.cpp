#include "projectile.h"

#include <iostream>
Projectile::Projectile(unsigned int unique_id, int x, int y, int type,
                       char repr, const unsigned int damage,
                       const bool critical, const unsigned int attacker_id,
                       const unsigned int range,
                       const orientation_t orientation, Map *map)
    : Entity(unique_id, x, y, type, repr),
      collided(false),
      damage(damage),
      critical(critical),
      attacker_id(attacker_id),
      range(range),
      orientation(orientation),
      map(map),
      collided_entity(-1) {
  impact_at_position(x, y);
  this->range--;
}

void Projectile::auto_move() {
  if (this->range == 0) {
    this->alive = false;
  }
  if (collided || !alive) return;
  if (range == 0) ModelException("El proyectil ya no puede moverse!");
  int next_x = x_position + get_next_x();
  int next_y = y_position + get_next_y();
  impact_at_position(next_x, next_y);
  range--;
  if (range == 0) {
    alive = false;
  }
}

void Projectile::impact_at_position(int x, int y) {
  std::cout << "calling impact at possition!" << std::endl;
  if (map->tile_is_safe(x, y)) {
    kill();
    return;
  } else if (map->can_ocupy_cell(x, y)) {
    map->empty_projectile(x_position, y_position);
    map->put_projectile(x, y);
    x_position = x;
    y_position = y;
  } else if (map->tile_is_valid(x, y)) {
    collided_entity = map->get_uid(x, y);
    collided = true;
  }
}

int Projectile::get_collided_entity() { return collided_entity; }

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

unsigned int Projectile::get_damage() { return damage; }
bool Projectile::is_critical() { return critical; }

unsigned int Projectile::get_attacker_id() { return attacker_id; }

void Projectile::kill() {
  // map->empty_cell(x_position, y_position);
  map->empty_projectile(x_position, y_position);
  alive = false;
}

Projectile::~Projectile() {}
