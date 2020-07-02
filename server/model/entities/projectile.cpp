#include "projectile.h"

#include <iostream>
Projectile::Projectile(int x, int y, int type, char repr,
                       const unsigned int damage, const bool critical,
                       const unsigned int attacker_id, const unsigned int range)
    : Entity(x, y, type, repr),
      damage(damage),
      critical(critical),
      attacker_id(attacker_id),
      range(range) {}

void Projectile::update() {}
Projectile::~Projectile() {}
