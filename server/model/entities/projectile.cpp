#include "projectile.h"
#include <iostream>
Projectile::Projectile(int x, int y, int type, char repr)
     : Entity(x, y, type, repr) {}

void Projectile::update() {

}
Projectile::~Projectile() {}
