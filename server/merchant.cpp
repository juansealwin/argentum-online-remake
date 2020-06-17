#include "merchant.h"
#include <iostream>
Merchant::Merchant(int x, int y, int type, char repr)
     : Entity(x, y, type, repr) {}

void Merchant::update() {
  //std::cout << "Trying to update Merchant, to be implemented" << std::endl;
}
Merchant::~Merchant() {}
