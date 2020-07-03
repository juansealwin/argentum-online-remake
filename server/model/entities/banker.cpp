#include "banker.h"
#include <iostream>
Banker::Banker(unsigned int unique_id, int x, int y, int type, char repr)
     : Entity(unique_id, x, y, type, repr) {}

Banker::~Banker() {}
