#include "merchant.h"
#include <iostream>
Merchant::Merchant(unsigned int unique_id, int x, int y, int type, char repr)
     : Entity(unique_id, x, y, type, repr) {}

Merchant::~Merchant() {}
