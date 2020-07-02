#include "projectile.h"

#include <iostream>
Projectile::Projectile(unsigned int unique_id, int x, int y, int type, char repr,
                       const unsigned int damage, const bool critical,
                       const unsigned int attacker_id, const unsigned int range,
                       const orientation_t orientation, Map *map)
    : Entity(unique_id, x, y, type, repr),
      damage(damage),
      critical(critical),
      attacker_id(attacker_id),
      range(range), 
      orientation(orientation),
      map(map) {}

void Projectile::update() {}
Projectile::~Projectile() {}
