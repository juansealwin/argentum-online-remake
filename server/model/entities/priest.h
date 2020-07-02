
#ifndef PRIEST_H
#define PRIEST_H
#include "entity.h"
#include "stdint.h"
class Priest : public Entity {
 public:
  Priest(unsigned int unique_id, int x, int y, int type, char repr);
  virtual ~Priest();
  Priest(const Priest &) = delete;
  // En este update() se podria hacer algo como renovar el stock del priest
  void update() override;
};

#endif  // PRIEST_H
