#ifndef MERCHANT_H
#define MERCHANT_H
#include "entity.h"
#include "stdint.h"
class Merchant : public Entity {
 public:
  Merchant(unsigned int unique_id, int x, int y, int type, char repr);
  virtual ~Merchant();
  Merchant(const Merchant &) = delete;

};

#endif  // MERCHANT_H
