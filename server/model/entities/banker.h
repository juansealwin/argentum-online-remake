#include "entity.h"
#include "stdint.h"
#ifndef BANKER_H
#define BANKER_H
class Banker : public Entity {
 public:
  Banker(unsigned int unique_id, int x, int y, int type, char repr);
  virtual ~Banker();
  Banker(const Banker &) = delete;
};

#endif  // BANKER_H
