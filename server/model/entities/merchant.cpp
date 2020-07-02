#include "merchant.h"
#include <iostream>
Merchant::Merchant(unsigned int unique_id, int x, int y, int type, char repr)
     : Entity(unique_id, x, y, type, repr) {}

void Merchant::update() {
  //std::cout << "Trying to update Merchant, to be implemented" << std::endl;
}
Merchant::~Merchant() {}
