
#ifndef PRIEST_H
#define PRIEST_H
#include "entity.h"
#include "stdint.h"
class Priest : public Entity {
 public:
  Priest(unsigned int unique_id, int x, int y, int type, char repr);
  virtual ~Priest();
  Priest(const Priest &) = delete;
  
};

#endif  // PRIEST_H
