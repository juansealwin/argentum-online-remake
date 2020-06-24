#include "entity.h"
#include "stdint.h"
#ifndef MERCHANT_H
#define MERCHANT_H
class Merchant : public Entity {
 public:
  Merchant(int x, int y, int type, char repr);
  virtual ~Merchant();
  Merchant(const Merchant &) = delete;
  // En este update() se podria hacer algo como renovar el stock del merchant
  void update() override;
};

#endif  // MERCHANT_H
