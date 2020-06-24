#include "entity.h"
#include "stdint.h"
#ifndef PRIEST_H
#define PRIEST_H
class Priest : public Entity {
 public:
  Priest(int x, int y, int type, char repr);
  virtual ~Priest();
  Priest(const Priest &) = delete;
  // En este update() se podria hacer algo como renovar el stock del priest
  void update() override;
};

#endif  // PRIEST_H
