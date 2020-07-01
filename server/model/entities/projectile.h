#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "entity.h"
#include "model_exceptions.h"
class Projectile : Entity {
 public:
  Projectile(int x, int y, int type, char repr);
  virtual ~Projectile();
  Projectile(const Projectile &) = delete;
  // Mover proyectil, chequear colision
  void update() override;
};

#endif  // PROJECTILE_H
